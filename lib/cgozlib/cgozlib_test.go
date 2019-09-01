// Copyright 2019 The Wuffs Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

package cgozlib

import (
	"bytes"
	"compress/zlib"
	"io"
	"io/ioutil"
	"strings"
	"testing"
)

// These examples come from the RAC spec.
var (
	compressedMore = "\x78\x9c\x01\x06\x00\xf9\xff\x4d\x6f\x72\x65\x21" +
		"\x0a\x07\x42\x01\xbf"

	compressedSheep = "\x78\xf9\x0b\xe0\x02\x6e\x0a\x29\xcf\x87\x31\x01\x01" +
		"\x00\x00\xff\xff\x18\x0c\x03\xa8"

	dictSheep = []byte("\x20sheep.\n")
)

type resetReadCloser interface {
	zlib.Resetter
	io.ReadCloser
}

func makePure() resetReadCloser {
	r, err := zlib.NewReader(strings.NewReader(compressedMore))
	if err != nil {
		panic(err.Error())
	}
	return r.(resetReadCloser)
}

func testReadAll(t *testing.T, r resetReadCloser, src io.Reader, dict []byte, want string) {
	t.Helper()

	if err := r.Reset(src, dict); err != nil {
		t.Fatalf("Reset: %v", err)
	}

	got, err := ioutil.ReadAll(r)
	if err != nil {
		t.Fatalf("ReadAll: %v", err)
	}

	if err := r.Close(); err != nil {
		t.Fatalf("Close: %v", err)
	}

	if string(got) != want {
		t.Fatalf("got %q, want %q", got, want)
	}
}

func testReader(t *testing.T, r resetReadCloser) {
	testReadAll(t, r, strings.NewReader(compressedMore), nil, "More!\n")
	testReadAll(t, r, strings.NewReader(compressedSheep), dictSheep, "Two sheep.\n")
	testReadAll(t, r, strings.NewReader(compressedMore), nil, "More!\n")
	testReadAll(t, r, strings.NewReader(compressedSheep), dictSheep, "Two sheep.\n")
}

func TestCgo(t *testing.T)  { testReader(t, &Reader{}) }
func TestPure(t *testing.T) { testReader(t, makePure()) }

func benchmarkReader(b *testing.B, r resetReadCloser) {
	src := bytes.NewReader(nil)
	srcBytes, err := ioutil.ReadFile("../../test/data/pi.txt.zlib")
	if err != nil {
		b.Fatalf("ReadFile: %v", err)
	}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		src.Reset(srcBytes)

		if err := r.Reset(src, nil); err != nil {
			b.Fatalf("Reset: %v", err)
		}

		if n, err := io.Copy(ioutil.Discard, r); err != nil {
			b.Fatalf("Copy: %v", err)
		} else if n != 100003 {
			b.Fatalf("Copy: got %d, want %d", n, 100003)
		}

		if err := r.Close(); err != nil {
			b.Fatalf("Close: %v", err)
		}
	}
}

func BenchmarkCgo(b *testing.B)  { benchmarkReader(b, &Reader{}) }
func BenchmarkPure(b *testing.B) { benchmarkReader(b, makePure()) }
