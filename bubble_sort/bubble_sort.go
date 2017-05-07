package main

import "fmt"

func swap(dataset []int, a, b int) {
	x := dataset[a]
	dataset[a] = dataset[b]
	dataset[b] = x
}

func bubbleSort(dataset []int, amountOfIntegers int) {
	for i := 0; i <= amountOfIntegers; i++ {
		for j := amountOfIntegers; j >= i+1; j-- {
			if dataset[j] < dataset[j-1] {
				swap(dataset, j, j-1)
			}
		}
	}
}

func test(x int) int {
	return x * x
}

func main() {
	dataset := []int{5, 2, 4, 6, 1, 3}

	fmt.Println(dataset)

	bubbleSort(dataset, 5)

	fmt.Println(dataset)
}
