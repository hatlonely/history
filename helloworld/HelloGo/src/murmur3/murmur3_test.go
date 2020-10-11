package hash

import (
	"crypto/md5"
	"crypto/sha256"
	"encoding/base64"
	"encoding/binary"
	"encoding/hex"
	"fmt"
	"github.com/spaolacci/murmur3"
	"testing"
)

func TestMurmur3(t *testing.T) {
	fmt.Println(murmur3.Sum64([]byte("hello world")))
}

func TestMd5(t *testing.T) {
	h := md5.New()
	h.Write([]byte("hello world"))
	fmt.Println("md5: ", hex.EncodeToString(h.Sum(nil)))
	h.Write([]byte("hello world"))
	fmt.Println("md5: ", hex.EncodeToString(h.Sum(nil)))
	h.Reset()
	h.Write([]byte("hello worldhello world"))
	fmt.Println("md5: ", hex.EncodeToString(h.Sum(nil)))
}

func TestSha256(t *testing.T) {
	h := sha256.New()
	h.Write([]byte("hello world"))
	fmt.Println("sha256: ", hex.EncodeToString(h.Sum(nil)))
}

func TestBase64(t *testing.T) {
	fmt.Println(base64.StdEncoding.EncodeToString([]byte("hello world")))

	buf, err := base64.StdEncoding.DecodeString("aGVsbG8gd29ybGQ=")
	fmt.Println(string(buf), err)
}

func TestBinary(t *testing.T) {
	buf := make([]byte, 8)
	binary.LittleEndian.PutUint64(buf, 100)
	fmt.Println(binary.LittleEndian.Uint64(buf))
}
