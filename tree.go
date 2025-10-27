package main

import "fmt"

type TNode struct {
	Data   string
	Left   *TNode
	Right  *TNode
	Height int
}

type BinaryTree struct {
	Root *TNode
	Size int
}

func getHeight(node *TNode) int {
	if node == nil {
		return 0
	}
	return node.Height
}

func updateHeight(node *TNode) {
	if node != nil {
		leftHeight := getHeight(node.Left)
		rightHeight := getHeight(node.Right)
		if leftHeight > rightHeight {
			node.Height = 1 + leftHeight
		} else {
			node.Height = 1 + rightHeight
		}
	}
}

func getBalance(node *TNode) int {
	if node == nil {
		return 0
	}
	return getHeight(node.Left) - getHeight(node.Right)
}

func createTNode(data string) *TNode {
	return &TNode{
		Data:   data,
		Left:   nil,
		Right:  nil,
		Height: 1,
	}
}

func rotateRight(y *TNode) *TNode {
	x := y.Left
	T2 := x.Right

	x.Right = y
	y.Left = T2

	updateHeight(y)
	updateHeight(x)

	return x
}

func rotateLeft(x *TNode) *TNode {
	y := x.Right
	T2 := y.Left

	y.Left = x
	x.Right = T2

	updateHeight(x)
	updateHeight(y)

	return y
}

func balance(node *TNode) *TNode {
	if node == nil {
		return nil
	}

	updateHeight(node)
	bal := getBalance(node)

	// Left-Left
	if bal > 1 && getBalance(node.Left) >= 0 {
		return rotateRight(node)
	}

	// Left-Right
	if bal > 1 && getBalance(node.Left) < 0 {
		node.Left = rotateLeft(node.Left)
		return rotateRight(node)
	}

	// Right-Right
	if bal < -1 && getBalance(node.Right) <= 0 {
		return rotateLeft(node)
	}

	// Right-Left
	if bal < -1 && getBalance(node.Right) > 0 {
		node.Right = rotateRight(node.Right)
		return rotateLeft(node)
	}

	return node
}

func insertNode(node *TNode, data string, inserted *bool) *TNode {
	if node == nil {
		*inserted = true
		return createTNode(data)
	}

	if data < node.Data {
		node.Left = insertNode(node.Left, data, inserted)
	} else if data > node.Data {
		node.Right = insertNode(node.Right, data, inserted)
	} else {
		return node
	}

	return balance(node)
}

func findMin(node *TNode) *TNode {
	for node != nil && node.Left != nil {
		node = node.Left
	}
	return node
}

func deleteNode(node *TNode, data string, deleted *bool) *TNode {
	if node == nil {
		return nil
	}

	if data < node.Data {
		node.Left = deleteNode(node.Left, data, deleted)
	} else if data > node.Data {
		node.Right = deleteNode(node.Right, data, deleted)
	} else {
		*deleted = true

		if node.Left == nil || node.Right == nil {
			if node.Left != nil {
				return node.Left
			}
			return node.Right
		}

		temp := findMin(node.Right)
		node.Data = temp.Data
		node.Right = deleteNode(node.Right, temp.Data, deleted)
		*deleted = true
	}

	return balance(node)
}

func CreateTree() *BinaryTree {
	return &BinaryTree{
		Root: nil,
		Size: 0,
	}
}

func (tree *BinaryTree) Push(data string) {
	inserted := false
	tree.Root = insertNode(tree.Root, data, &inserted)
	if inserted {
		tree.Size++
	}
}

func (tree *BinaryTree) Delete(data string) {
	deleted := false
	tree.Root = deleteNode(tree.Root, data, &deleted)
	if deleted {
		tree.Size--
	}
}

func (tree *BinaryTree) Search(data string) bool {
	current := tree.Root
	for current != nil {
		if data == current.Data {
			return true
		} else if data < current.Data {
			current = current.Left
		} else {
			current = current.Right
		}
	}
	return false
}

func (tree *BinaryTree) PrintTree() {
	if tree.Root == nil {
		fmt.Println("Дерево пустое")
		return
	}

	q := CreateQueue()
	q.Push(fmt.Sprintf("%p", tree.Root))

	level := 0
	nodesInLevel := 1
	nodesInNext := 0

	fmt.Printf("Уровень %d: ", level)

	for q.Size > 0 {
		ptrStr := q.Pop()
		var current *TNode
		fmt.Sscanf(ptrStr, "%p", &current)

		fmt.Print(current.Data)
		nodesInLevel--

		if current.Left != nil {
			q.Push(fmt.Sprintf("%p", current.Left))
			nodesInNext++
		}
		if current.Right != nil {
			q.Push(fmt.Sprintf("%p", current.Right))
			nodesInNext++
		}

		if nodesInLevel > 0 {
			fmt.Print(" ")
		} else {
			fmt.Println()
			if nodesInNext > 0 {
				level++
				fmt.Printf("Уровень %d: ", level)
				nodesInLevel = nodesInNext
				nodesInNext = 0
			}
		}
	}
}

func preOrder(node *TNode) {
	if node == nil {
		return
	}
	fmt.Print(node.Data, " ")
	preOrder(node.Left)
	preOrder(node.Right)
}

func inOrder(node *TNode) {
	if node == nil {
		return
	}
	inOrder(node.Left)
	fmt.Print(node.Data, " ")
	inOrder(node.Right)
}

func postOrder(node *TNode) {
	if node == nil {
		return
	}
	postOrder(node.Left)
	postOrder(node.Right)
	fmt.Print(node.Data, " ")
}