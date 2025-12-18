package main

import (
	"testing"
	"github.com/stretchr/testify/assert"
)

func TestHelpFunctions(t *testing.T) {
	// Тестируем функции помощи
	assert.NotPanics(t, func() {
		printGeneralHelp()
	})

	assert.NotPanics(t, func() {
		printArrayHelp()
	})

	assert.NotPanics(t, func() {
		printSinglyListHelp()
	})

	assert.NotPanics(t, func() {
		printDoublyListHelp()
	})

	assert.NotPanics(t, func() {
		printStackHelp()
	})

	assert.NotPanics(t, func() {
		printQueueHelp()
	})

	assert.NotPanics(t, func() {
		printHashTableHelp()
	})
}
