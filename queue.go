package main

import "fmt"

type QNode struct {
	Data string
	Next *QNode
}

type Queue struct {
	Head *QNode
	Tail *QNode
	Size int
}

func CreateQueue() *Queue {
	return &Queue{
		Head: nil,
		Tail: nil,
		Size: 0,
	}
}

func (queue *Queue) Push(data string) {
	newNode := &QNode{
		Data: data,
		Next: nil,
	}

	if queue.Tail != nil {
		queue.Tail.Next = newNode
	} else {
		queue.Head = newNode
	}

	queue.Tail = newNode
	queue.Size++
}

func (queue *Queue) Pop() string {
	if queue.Size == 0 {
		return ""
	}

	element := queue.Head.Data
	queue.Head = queue.Head.Next

	if queue.Head == nil {
		queue.Tail = nil
	}

	queue.Size--
	return element
}

func (queue *Queue) Print() {
	fmt.Print("[")
	current := queue.Head
	for i := 0; i < queue.Size; i++ {
		fmt.Print(current.Data)
		if i < queue.Size-1 {
			fmt.Print(", ")
		}
		current = current.Next
	}
	fmt.Println("]")
}