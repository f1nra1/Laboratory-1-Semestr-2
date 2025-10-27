package main

import "fmt"

type SNode struct {
	Data string
	Next *SNode
}

type Stack struct {
	Top  *SNode
	Size int
}

func CreateStack() *Stack {
	return &Stack{
		Top:  nil,
		Size: 0,
	}
}

func (stack *Stack) Push(data string) {
	newNode := &SNode{
		Data: data,
		Next: stack.Top,
	}
	stack.Top = newNode
	stack.Size++
}

func (stack *Stack) Pop() string {
	if stack.Top == nil {
		return ""
	}
	data := stack.Top.Data
	stack.Top = stack.Top.Next
	stack.Size--
	return data
}

func (stack *Stack) Print() {
	fmt.Print("[")
	current := stack.Top
	first := true
	for current != nil {
		if !first {
			fmt.Print(", ")
		}
		fmt.Print(current.Data)
		current = current.Next
		first = false
	}
	fmt.Println("]")
}