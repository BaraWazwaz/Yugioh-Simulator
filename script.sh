#!/usr/bin/env bash

set -e

log() {
    echo "$@" >&2
}

prepare() {
    log "⚙️  Preparing CMake generation and build process..."
    
    if [ ! -d "build" ]; then
        mkdir build
        log "📁 Created 'build' directory."
    fi
    
    cd build
    
    log "🧹 Cleaning previous build cache..."
    rm -rf CMakeCache.txt CMakeFiles/
    
    log "🔨 Generating build system..."
    cmake -G "MinGW Makefiles" ..

    log "✅ Success! CMake project was prepared"
    cd ..
}

compile() {
    log "🚀 Compiling source code..."
    
    if cmake --build build; then
        log "✅ Success! Output created in dist/program.exe"
        return 0
    else
        log "❌ Error: Failed to build"
        return 1
    fi
}

run() {
    shift
    log "🚀 Running program..."
    
    if [[ ! -f "dist/program.exe" ]]; then
        log "❌ dist/program.exe was not found..."
        
        set +e
        compile
        local compile_status=$?
        set -e

        if [ $compile_status -ne 0 ]; then
            return $compile_status
        fi
    fi

    set +e
    ./dist/program.exe "$@"
    local run_status=$?
    set -e
    
    if [ $run_status -eq 0 ]; then
        log "✅ Exited with status code 0"
    else
        log "❌ Exited with status code $run_status"
    fi

    return $run_status
}

show_help() {
    log "❌ Error: Invalid or missing argument."
    log "💡 Usage: ./script.sh [command]"
    log "Available commands:"
    log "  prepare  - Generate CMake build files"
    log "  compile  - Compile the program"
    log "  run      - Run the program (e.g. ./script.sh run --arg1 --arg2)"
}

main() {
    local command="$1"

    case "$command" in
        "prepare")
            prepare
            ;;
        "compile")
            compile
            ;;
        "run")
            run "$@"
            ;;
        *)
            show_help
            exit 1
            ;;
    esac
}

main "$@"
