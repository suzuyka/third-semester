package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {

	var plantUML strings.Builder
	plantUML.WriteString("@startuml\n")
	plantUML.WriteString("title Go Data Structures UML\n\n")

	// Основные классы проекта
	classes := []string{
		"Array", "SinglyLinkedList", "DoublyLinkedList",
		"Stack", "Queue", "HashTable",
	}

	for _, className := range classes {
		plantUML.WriteString(fmt.Sprintf("class %s\n", className))
	}

	// Добавляем основные методы для каждого класса
	plantUML.WriteString(`
	class Array {
	+ Push(value: int)
	+ Insert(index: int, value: int): bool
	+ Get(index: int): int
	+ Set(index: int, value: int): bool
	+ Delete(index: int): bool
	+ Print()
}

class SinglyLinkedList {
+ PushBack(value: int)
	+ PushFront(value: int)
	+ InsertBefore(target: int, value: int): bool
	+ InsertAfter(target: int, value: int): bool
	+ Delete(value: int): bool
	+ Get(index: int): int
}

class DoublyLinkedList {
+ PushBack(value: int)
	+ PushFront(value: int)
	+ InsertBefore(target: int, value: int): bool
	+ InsertAfter(target: int, value: int): bool
	+ Delete(value: int): bool
}

class Stack {
+ Push(value: int)
	+ Pop(): (int, bool)
	+ Print()
}

class Queue {
+ Push(value: int)
	+ Pop(): (int, bool)
	+ Print()
}

class HashTable {
+ Insert(key: int, value: int)
	+ Get(key: int): (int, bool)
	+ Remove(key: int): bool
	+ Print()
	+ loadFactor(): float64
}
`)

	// Связи
	plantUML.WriteString(`
	HashTable --> Array
	SinglyLinkedList --> Array
	DoublyLinkedList --> Array
	Stack --> Array
	Queue --> Array

	note top of HashTable
	Three hash methods:
	• DOUBLE_HASHING
	• CUCKOO_HASHING
	• FOLDING_HASHING
	end note

	note bottom of Array
	Dynamic array implementation
	with automatic resizing
	end note
	`)

	plantUML.WriteString("@enduml\n")

	// Сохраняем PlantUML
	os.WriteFile("project_uml.puml", []byte(plantUML.String()), 0644)

	// Создаем HTML
	generateStandaloneHTML(plantUML.String())

	fmt.Println("✅ UML generated: project_uml.puml")
	fmt.Println("✅ Standalone HTML: uml_standalone.html")
}

func generateStandaloneHTML(umlCode string) {
	html := `<!DOCTYPE html>
	<html>
	<head>
	<title>Go Project UML - Standalone</title>
	<meta charset="UTF-8">
	<style>
	body {
	font-family: Arial, sans-serif;
	margin: 0;
	padding: 20px;
	background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
	min-height: 100vh;
}
.container {
max-width: 1200px;
margin: 0 auto;
background: white;
padding: 30px;
border-radius: 15px;
box-shadow: 0 10px 30px rgba(0,0,0,0.2);
}
h1 {
color: #333;
text-align: center;
margin-bottom: 30px;
border-bottom: 3px solid #4CAF50;
padding-bottom: 10px;
}
.uml-container {
background: #f8f9fa;
border: 2px solid #e9ecef;
border-radius: 10px;
padding: 20px;
margin: 20px 0;
}
.code-container {
background: #2d3748;
color: #e2e8f0;
padding: 20px;
border-radius: 8px;
margin: 20px 0;
overflow-x: auto;
}
pre {
margin: 0;
font-family: 'Courier New', monospace;
font-size: 14px;
line-height: 1.4;
}
.instructions {
background: #e8f5e8;
border-left: 4px solid #4CAF50;
padding: 15px;
margin: 20px 0;
border-radius: 0 8px 8px 0;
}
.btn {
background: #4CAF50;
color: white;
padding: 12px 24px;
text-decoration: none;
border-radius: 6px;
display: inline-block;
margin: 10px 5px;
border: none;
cursor: pointer;
font-size: 16px;
}
.btn:hover {
background: #45a049;
}
</style>
</head>
<body>
<div class="container">
<h1>🚀 Go Data Structures UML Diagram</h1>

<div class="instructions">
<h3>📋 How to view the diagram:</h3>
<p>1. Copy the PlantUML code below</p>
<p>2. Go to <a href="https://www.plantuml.com/plantuml/" target="_blank">PlantUML Online</a></p>
<p>3. Paste the code and view your UML diagram</p>
</div>

<div style="text-align: center; margin: 20px 0;">
<button class="btn" onclick="copyCode()">📋 Copy PlantUML Code</button>
<a class="btn" href="project_uml.puml" download>💾 Download .puml File</a>
<a class="btn" href="https://www.plantuml.com/plantuml/" target="_blank">🌐 Open PlantUML Online</a>
</div>

<div class="code-container">
<pre id="umlCode">` + umlCode + `</pre>
</div>

<div class="instructions">
<h3>🎯 Project Structure Overview:</h3>
<ul>
<li><strong>Array</strong> - Dynamic array with automatic resizing</li>
<li><strong>SinglyLinkedList</strong> - Single-linked list implementation</li>
<li><strong>DoublyLinkedList</strong> - Double-linked list implementation</li>
<li><strong>Stack</strong> - LIFO data structure</li>
<li><strong>Queue</strong> - FIFO data structure</li>
<li><strong>HashTable</strong> - Hash table with 3 collision resolution methods</li>
</ul>
</div>
</div>

<script>
function copyCode() {
const code = document.getElementById('umlCode').textContent;
navigator.clipboard.writeText(code).then(() => {
alert('✅ PlantUML code copied to clipboard!');
}).catch(err => {
console.error('Failed to copy: ', err);
});
}

// Auto-select code on click for easy copying
document.getElementById('umlCode').addEventListener('click', function() {
const range = document.createRange();
range.selectNodeContents(this);
const selection = window.getSelection();
selection.removeAllRanges();
selection.addRange(range);
});
</script>
</body>
</html>`

os.WriteFile("uml_standalone.html", []byte(html), 0644)
}
