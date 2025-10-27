package main

import "fmt"

type LNode struct {
	Data  string
	Next  *LNode
	Prev  *LNode
}

type LList struct {
	Size int
	Head *LNode
	Tail *LNode
}

func CreateLList() *LList {
	return &LList{
		Size: 0,
		Head: nil,
		Tail: nil,
	}
}

func CreateLNode(data string) *LNode {
	return &LNode{
		Data: data,
		Next: nil,
		Prev: nil,
	}
}

func (llist *LList) PushHead(data string) {
	newNode := CreateLNode(data)
	if llist.Head == nil {
		llist.Head = newNode
		llist.Tail = newNode
	} else {
		newNode.Next = llist.Head
		llist.Head.Prev = newNode
		llist.Head = newNode
	}
	llist.Size++
}

func (llist *LList) PushTail(data string) {
	newNode := CreateLNode(data)
	if llist.Head == nil {
		llist.Head = newNode
		llist.Tail = newNode
	} else {
		newNode.Prev = llist.Tail
		llist.Tail.Next = newNode
		llist.Tail = newNode
	}
	llist.Size++
}

func (llist *LList) PushBefore(data, element string) {
	if llist.Head == nil {
		return
	}
	if llist.Head.Data == element {
		llist.PushHead(data)
		return
	}
	current := llist.Head
	for current != nil && current.Data != element {
		current = current.Next
	}
	if current != nil {
		newNode := CreateLNode(data)
		newNode.Next = current
		newNode.Prev = current.Prev
		if current.Prev != nil {
			current.Prev.Next = newNode
		}
		current.Prev = newNode
		llist.Size++
	}
}

func (llist *LList) PushAfter(data, element string) {
	if llist.Head == nil {
		return
	}
	if llist.Tail.Data == element {
		llist.PushTail(data)
		return
	}
	current := llist.Head
	for current != nil && current.Data != element {
		current = current.Next
	}
	if current != nil {
		newNode := CreateLNode(data)
		newNode.Prev = current
		newNode.Next = current.Next
		if current.Next != nil {
			current.Next.Prev = newNode
		}
		current.Next = newNode
		llist.Size++
	}
}

func (llist *LList) PopHead() {
	if llist.Head == nil {
		return
	}
	llist.Head = llist.Head.Next
	if llist.Head != nil {
		llist.Head.Prev = nil
	} else {
		llist.Tail = nil
	}
	llist.Size--
}

func (llist *LList) PopTail() {
	if llist.Head == nil {
		return
	}
	if llist.Tail.Prev == nil {
		llist.Head = nil
		llist.Tail = nil
		llist.Size--
		return
	}
	llist.Tail = llist.Tail.Prev
	llist.Tail.Next = nil
	llist.Size--
}

func (llist *LList) PopElement(element string) {
	if llist.Head == nil {
		return
	}
	current := llist.Head
	for current != nil && current.Data != element {
		current = current.Next
	}
	if current != nil {
		if current.Prev == nil {
			llist.PopHead()
		} else if current.Next == nil {
			llist.PopTail()
		} else {
			current.Prev.Next = current.Next
			current.Next.Prev = current.Prev
			llist.Size--
		}
	}
}

func (llist *LList) Search(element string) bool {
	current := llist.Head
	for current != nil {
		if current.Data == element {
			return true
		}
		current = current.Next
	}
	return false
}

func (llist *LList) Print() {
	fmt.Print("[")
	current := llist.Head
	for current != nil {
		fmt.Print(current.Data)
		if current.Next != nil {
			fmt.Print(", ")
		}
		current = current.Next
	}
	fmt.Println("]")
}