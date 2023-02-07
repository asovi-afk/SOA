
package main

import (
	//"fmt"
	"github.com/lf-edge/ekuiper/sdk/go/api"
)

type Pair struct {
	repeats float64
	title	string
}

type register struct {
}

func (f *register) Validate(args []interface{}) error {
	return nil
}

// args[0] = [map[arr:[map[repeats:12 title:Moana] map[repeats:4 title:Sandman]]]]
func (f *register) Exec(args []interface{}, _ api.FunctionContext) (interface{}, bool) {
	var factor float64 = 0.4
	exptected_pairs := 10
	var min_num_of_requests uint64 = 3
	for_registration := make([]string,0, exptected_pairs)
	shell, ok := args[0].([]interface{})
	success := ok
	if ok {
		// shell[0] = map[arr:[map[repeats:12 title:Moana] map[repeats:4 title:Sandman]]]
		m_arr, ok := shell[0].(map[string]interface{})
		success = ok
		if ok {
			// m_arr["arr"] = [map[repeats:12 title:Moana] map[repeats:4 title:Sandman]]
			_arr, ok := m_arr["arr"].([]interface{})
			success = ok
			if ok {
				// _arr = [interface1{} interface2{} ...]
				// for each value in _arr
				var total uint64 = 0
				pairs := make([]Pair, 0, exptected_pairs)
				for _, pair := range _arr {
					p, ok := pair.(map[string]interface{})
					if ok {
						rep, _ok1 := p["repeats"].(float64)
						tit, _ok2 := p["title"].(string)
						if !(_ok1 && _ok2) {
							return for_registration, false
						}
						pairs = append(pairs, Pair{rep, tit})
						total += uint64(rep)
					} else {
						return for_registration, false
					}
				}
				if total >= min_num_of_requests {
					for _, pair := range pairs {
						if pair.repeats / float64(total) >= factor {
							for_registration = append(for_registration, pair.title)
						}
					}
				}
			}
		}
	}
	return for_registration, success
}

func (f *register) IsAggregate() bool {
	return true
}
