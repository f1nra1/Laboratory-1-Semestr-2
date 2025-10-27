package main

import "fmt"

type MArray struct {
	Data     []string
	Size     int
	Capacity int
}

func CreateMArray(capacity int) *MArray {
	if capacity <= 0 {
		capacity = 10
	}
	return &MArray{
		Data:     make([]string, capacity),
		Size:     0,
		Capacity: capacity,
	}
}

func (arr *MArray) Resize() {
	newCapacity := arr.Capacity * 2
	newData := make([]string, newCapacity)
	copy(newData, arr.Data[:arr.Size])
	arr.Data = newData
	arr.Capacity = newCapacity
}

func (arr *MArray) PushBack(element string) {
	if arr.Size == arr.Capacity {
		arr.Resize()
	}
	arr.Data[arr.Size] = element
	arr.Size++
}

func (arr *MArray) PushIndex(element string, index int) {
	if index < 0 || index > arr.Size {
		return
	}
	if arr.Size >= arr.Capacity {
		arr.Resize()
	}
	for i := arr.Size; i > index; i-- {
		arr.Data[i] = arr.Data[i-1]
	}
	arr.Data[index] = element
	arr.Size++
}

func (arr *MArray) Get(index int) string {
	if index < 0 || index >= arr.Size {
		return ""
	}
	return arr.Data[index]
}

func (arr *MArray) PopIndex(index int) {
	if arr.Size == 0 || index < 0 || index >= arr.Size {
		return
	}
	for i := index; i < arr.Size-1; i++ {
		arr.Data[i] = arr.Data[i+1]
	}
	arr.Size--
}

func (arr *MArray) Replace(element string, index int) {
	if index < 0 || index >= arr.Size {
		return
	}
	arr.Data[index] = element
}

func (arr *MArray) GetSize() int {
	return arr.Size
}

func (arr *MArray) Print() {
	fmt.Print("[")
	for i := 0; i < arr.Size; i++ {
		fmt.Print(arr.Data[i])
		if i < arr.Size-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println("]")
}