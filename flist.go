package main

import "fmt"

type FNode struct {
	Data string
	Next *FNode
}

type FList struct {
	Size int
	Head *FNode
}

func CreateFList() *FList {
	return &FList{
		Size: 0,
		Head: nil,
	}
}

func CreateFNode(data string) *FNode {
	return &FNode{
		Data: data,
		Next: nil,
	}
}

func (flist *FList) PushHead(data string) {
	newNode := CreateFNode(data)
	newNode.Next = flist.Head
	flist.Head = newNode
	flist.Size++
}

func (flist *FList) PushBack(data string) {
	newNode := CreateFNode(data)
	if flist.Head == nil {
		flist.Head = newNode
	} else {
		current := flist.Head
		for current.Next != nil {
			current = current.Next
		}
		current.Next = newNode
	}
	flist.Size++
}

func (flist *FList) PushBefore(data, element string) {
	if flist.Head == nil {
		return
	}
	if flist.Head.Data == element {
		flist.PushHead(data)
		return
	}
	current := flist.Head
	for current.Next != nil && current.Next.Data != element {
		current = current.Next
	}
	if current.Next != nil {
		newNode := CreateFNode(data)
		newNode.Next = current.Next
		current.Next = newNode
		flist.Size++
	}
}

func (flist *FList) PushAfter(data, element string) {
	current := flist.Head
	for current != nil {
		if current.Data == element {
			newNode := CreateFNode(data)
			newNode.Next = current.Next
			current.Next = newNode
			flist.Size++
			return
		}
		current = current.Next
	}
}

func (flist *FList) PopHead() {
	if flist.Head == nil {
		return
	}
	flist.Head = flist.Head.Next
	flist.Size--
}

func (flist *FList) PopTail() {
	if flist.Head == nil {
		return
	}
	if flist.Head.Next == nil {
		flist.Head = nil
		flist.Size--
		return
	}
	current := flist.Head
	for current.Next.Next != nil {
		current = current.Next
	}
	current.Next = nil
	flist.Size--
}

func (flist *FList) PopElement(element string) {
	if flist.Head == nil {
		return
	}
	if flist.Head.Data == element {
		flist.PopHead()
		return
	}
	current := flist.Head
	for current.Next != nil && current.Next.Data != element {
		current = current.Next
	}
	if current.Next != nil {
		current.Next = current.Next.Next
		flist.Size--
	}
}

func (flist *FList) Search(element string) bool {
	current := flist.Head
	for current != nil {
		if current.Data == element {
			return true
		}
		current = current.Next
	}
	return false
}

func (flist *FList) Print() {
	fmt.Print("[")
	current := flist.Head
	for current != nil {
		fmt.Print(current.Data)
		if current.Next != nil {
			fmt.Print(", ")
		}
		current = current.Next
	}
	fmt.Println("]")
}