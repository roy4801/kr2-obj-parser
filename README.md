# kr2-ojb-parser

```bash
git clone --recursive https://github.com/kirakira-pp/kr2-obj-parser.git
```

- Already cloned?
```bash
git submodule update --init --recursive
```

## Testing

Run the comprehensive test suite:

```bash
# Build without graphics dependencies
cmake -DBUILD_GRAPHICS=OFF ..
make test_parser

# Run all tests
ctest

# Run individual test
ctest -R "BunnyObjParsing"
```

Test data is located in the `test_data/` directory. See `test_data/README.md` for details.

## Dependencies

- [glfw3](https://github.com/glfw/glfw)
  - `3.3.6`
- [glad](https://glad.dav1d.de/)
- [spdlog](https://github.com/gabime/spdlog)
  - `v1.9.2`
- [googletest](https://github.com/google/googletest)
  - For testing framework
