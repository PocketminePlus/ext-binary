# ext-binary
A high performance C++ PHP extension designed to be a drop in replacement for Pocketmine's native binary-utils library.
Providing an average improvement of 3x faster execution for binary related tasks, while retaining 100% api compatibility, no need to modify Pocketmine source code. (No FFI!)
While superceeded by Pocketmine's new Encoding extension, this extension provides a direct port of the PHP version of binary utils.

## Benchmarks
Performance comparison with 15,000 itterations, ran on a 13th Gen i7.

| Operation Category | PHP (ms) | C++ (ms) | Speedup | Improvement |
|-------------------|----------|----------|---------|-------------|
| **Binary Static Methods** | | | | |
| Boolean Operations | 2.481 | 2.137 | 1.2x | 16.1% |
| Byte Operations | 5.370 | 3.426 | 1.6x | 56.7% |
| Short Operations | 8.314 | 2.617 | 3.2x | 217.7% |
| Little-Endian Short Operations | 7.743 | 2.824 | 2.7x | 174.2% |
| Triad Operations | 8.923 | 3.816 | 2.3x | 133.8% |
| Integer Operations | 5.786 | 1.559 | **3.7x** | **271.1%** |
| Little-Endian Integer Operations | 5.941 | 1.573 | **3.8x** | **277.7%** |
| Float Operations | 3.645 | 1.082 | **3.4x** | **236.8%** |
| Little-Endian Float Operations | 2.083 | 0.975 | 2.1x | 113.6% |
| Sign Operations | 1.763 | 1.577 | 1.1x | 11.8% |
| **BinaryStream Operations** | | | | |
| Basic Stream Operations | 21.584 | 6.603 | 3.3x | 226.9% |
| Extended Stream Operations | 23.511 | 5.359 | **4.4x** | **338.7%** |
| Triad Stream Operations | 9.692 | 2.909 | 3.3x | 233.2% |
| **Real-World Simulation** | | | | |
| Network Packet Processing | 25.060 | 5.333 | **4.7x** | **369.9%** |


## Testing (AI)
Compatibility tests were written by AI to ensure results from binary opperations were complicit with Pocketmine's binary-utils. In addition to that, ext-binary was used on producation at hera.club, with no issues.

The test file can be found in ./tests

## Building
To build the extension for Pocketmine's php binaries, follow these steps.
```
EXT_BINARY_VERSION="1.0.0" // Github tagged version, add near other ext version constants

get_github_extension "binary" "$EXT_BINARY_VERSION" "xsuperr" "ext-binary" // Github account & repo name, add under other ext github fetches

--enable-binary // Add to the ./configure command as an argument
```
