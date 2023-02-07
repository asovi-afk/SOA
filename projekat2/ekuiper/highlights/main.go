
package main

import (
	"github.com/lf-edge/ekuiper/sdk/go/api"
	sdk "github.com/lf-edge/ekuiper/sdk/go/runtime"
	"os"
)

func main() {
	sdk.Start(os.Args, &sdk.PluginConfig{
		Name: "highlights",
		Functions: map[string]sdk.NewFunctionFunc{
			"register": func() api.Function {
				return &register{}
			},
		},
	})
}