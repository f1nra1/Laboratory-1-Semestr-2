package main

import (
	"os"
)

func main() {
	for i := 1; i < len(os.Args); i++ {
		if os.Args[i] == "--file" && i+1 < len(os.Args) {
			dataFile = os.Args[i+1]
			LoadDatabase()
			i++
		} else if os.Args[i] == "--query" && i+1 < len(os.Args) {
			ExecuteQuery(os.Args[i+1])
			i++
		}
	}
	CleanupDatabase()
}