package hclould

import (
	"fmt"
	"github.com/cihub/seelog"
	"io/ioutil"
	"os"
	"strings"
)

type Markdown struct {
	markdownDirectorys []string
}

func (m *Markdown) Init(markdownDirectorys []string) {
	m.markdownDirectorys = markdownDirectorys
	seelog.Infof("markdown init success. markdownDirectorys: [%v]", m.markdownDirectorys)
}

func (m *Markdown) DocList() *[]string {
	docs := []string{}
	for _, directory := range m.markdownDirectorys {
		infos, err := ioutil.ReadDir(directory)
		if err != nil {
			continue
		}
		for _, info := range infos {
			if strings.HasSuffix(info.Name(), ".md") {
				docs = append(docs, info.Name())
			}
		}
	}

	return &docs
}

func (m *Markdown) Document(filename string) (string, error) {
	for _, directory := range m.markdownDirectorys {
		filepath := fmt.Sprintf("%v/%v", directory, filename)
		if _, err := os.Stat(filepath); err == nil {
			data, err := ioutil.ReadFile(filepath)
			if err != nil {
				return "", err
			}
			return string(data), nil
		}
	}
	return "", seelog.Warnf("no such file. filename: [%v]", filename)
}
