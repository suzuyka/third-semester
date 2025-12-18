BINARY=project
SRC=main.go commands.go io.go slist.go dlist.go stack.go queue.go help.go hashtable.go serialize.go

all: build

build:
	@echo "Building..."
	@go build -o $(BINARY) $(SRC)
	@echo "Build complete: $(BINARY)"

run: build
	@echo "Running..."
	@./$(BINARY)

test:
	@echo "Running tests..."
	@go test -v ./...

coverage:
	@echo "📊 Generating coverage report..."
	@go test -coverprofile=coverage.out ./...
	@go tool cover -html=coverage.out -o coverage.html
	@echo "✅ HTML отчет создан: coverage.html"

bench:
	@echo "⚡ Running benchmarks only..."
	@go test -bench=. -benchmem -benchtime=2s -run="^$$" ./...

lint:
	@echo "🔍 Running go vet..."
	@go vet ./...
	@echo "🔍 Checking format..."
	@if [ -n "$$(gofmt -l .)" ]; then \
		echo "❌ Code is not formatted. Run 'make lint-fix'"; \
		exit 1; \
	fi
	@echo "✅ All lint checks passed!"

lint-fix:
	@echo "🔧 Fixing formatting..."
	@gofmt -w .
	@echo "✅ Formatting fixed!"

# UML Generation
uml-standalone:
	@echo "📊 Generating standalone UML..."
	@go run tools/uml_standalone.go
	@echo "✅ Open uml_standalone.html in your browser"

uml: uml-standalone
	@echo "🌐 Opening standalone UML..."
	@xdg-open uml_standalone.html 2>/dev/null || open uml_standalone.html 2>/dev/null || echo "✅ Open uml_standalone.html manually"

clean:
	@echo "🧹 Cleaning..."
	@rm -f $(BINARY) *.bin *.txt coverage.out coverage.html *.puml *.html
	@echo "✅ Clean complete"

help:
	@echo "🚀 Available commands:"
	@echo ""
	@echo "📦 Build & Run:"
	@echo "  make build      	- Build the project"
	@echo "  make run        	- Build and run the project"
	@echo "  make all        	- Build the project (alias for build)"
	@echo ""
	@echo "🧪 Testing:"
	@echo "  make test       	- Run all tests"
	@echo "  make coverage   	- Generate HTML coverage report"
	@echo "  make bench      	- Run benchmarks"
	@echo ""
	@echo "🔧 Code Quality:"
	@echo "  make lint       	- Run go vet and format checking"
	@echo "  make lint-fix   	- Fix formatting issues"
	@echo ""
	@echo "📊 Documentation:"
	@echo "  make uml        	- Generate UML diagrams and open in browser"
	@echo "  make uml-standalone 	- Generate UML diagrams only"
	@echo ""
	@echo "🧹 Cleanup:"
	@echo "  make clean      	- Remove built files and reports"
	@echo ""
	@echo "📋 Project Info:"
	@echo "  make help       	- Show this help message"

.PHONY: all build run test coverage bench lint lint-fix uml uml-standalone clean help
