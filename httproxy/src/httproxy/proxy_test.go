package httproxy

import (
	"reflect"
	"testing"
)

func TestInit(t *testing.T) {
	if err := Init("../../conf/offline/httproxy.json"); err != nil {
		t.Error(err)
	}
}

func TestFindPlaceholders(t *testing.T) {
	for _, unit := range []struct {
		originUrl    string
		placeholders []string
	}{
		{"{mini}:3001/{test}/abc", []string{"mini", "test"}},
		{"{mini}:3001/{test}/{abc", []string{"mini", "test"}},
	} {
		if placeholders := FindPlaceholders(unit.originUrl); !reflect.DeepEqual(placeholders, unit.placeholders) {
			t.Errorf("FindPlaceholder failed. unit: [%+v], placeholders: [%v]", unit, placeholders)
		}
	}
}

func TestProxy_FormatUrl(t *testing.T) {
	for _, unit := range []struct {
		originUrl string
		formatUrl string
	}{
		{"{mini}:3001/{test}/abc", ":3001//abc"},
	} {
		if formatUrl, err := proxy.FormatUrl(unit.originUrl); err != nil || formatUrl != unit.formatUrl {
			t.Errorf("Proxy FormatUrl failed. unit: [%+v], formatUrl: [%v], err: [%v]", unit, formatUrl, err)
		}
	}
}
