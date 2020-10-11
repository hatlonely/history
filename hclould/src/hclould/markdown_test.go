package hclould

import (
	"os"
	"reflect"
	"testing"
)

var markdown Markdown

func TestMarkdown_Init(t *testing.T) {
	markdown = Markdown{}
	markdown.Init([]string{"."})
}

func TestMarkdown_DocList(t *testing.T) {
	os.Create("test1.md")
	os.Create("test2.md")
	expected := &[]string{
		"test1.md", "test2.md",
	}
	if doclist := markdown.DocList(); !reflect.DeepEqual(doclist, expected) {
		t.Errorf("DocList() expected: [%v], doclist: [%v]", expected, doclist)
	}
	os.Remove("test1.md")
	os.Remove("test2.md")
}

func TestMarkdown_Document(t *testing.T) {
	fp, _ := os.Create("test1.md")
	defer fp.Close()
	fp.WriteString("轻轻的我走了，正如我轻轻的来。\n")
	fp.WriteString("我挥一挥衣袖，不带走一片云彩。\n")
	expected := "轻轻的我走了，正如我轻轻的来。\n我挥一挥衣袖，不带走一片云彩。\n"
	if doc, err := markdown.Document("test1.md"); err != nil || doc != expected {
		t.Errorf("expected: [%v, nil], actually: [%v, %v]", expected, doc, err)
	}
	os.Remove("test1.md")
}
