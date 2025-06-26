# COVID-19 CSV Data Fetcher & Parser

A C program that fetches COVID-19 data from online CSV APIs and parses it into structured data formats.

## 🚧 Project Status: Discontinued (For Now)

**This project has been discontinued as of June 26, 2025.**

I've decided to pause development on this CSV parser to focus on a more exciting project - building an **Interactive Weather Dashboard with HTTP Server**. The complexity of proper CSV parsing (handling quoted fields, escaped characters, etc.) became quite involved, and I want to explore other areas of C programming.

## What Was Accomplished ✅

- **✅ API Data Fetching**: Successfully implemented libcurl integration to fetch CSV data from remote APIs
- **✅ Memory Management**: Proper dynamic memory allocation and cleanup for data structures
- **✅ Basic CSV Parsing**: Implemented line-by-line parsing with `strtok`
- **✅ Data Structures**: Created comprehensive `s_CovidRecord` and `s_CovidData` structures
- **✅ Error Handling**: Robust error checking and memory leak prevention
- **✅ Modular Design**: Clean separation of concerns across multiple source files

## What Was Learned 📚

- **API Integration**: How to use libcurl for HTTP requests in C
- **Memory Management**: Dynamic allocation, reallocation, and proper cleanup
- **String Manipulation**: Working with `strtok`, `strdup`, and string parsing
- **Data Structures**: Designing containers for dynamic data
- **CSV Complexity**: Discovered the challenges of parsing CSV with quoted fields and embedded commas

## Current Issues 🐛

- **Complex CSV Parsing**: The real-world COVID CSV contains quoted fields with embedded commas (e.g., `"New York City, New York, US"`)
- **Field Parsing**: Simple `strtok(line, ",")` approach breaks on quoted fields
- **Only Parsing 1 Record**: Due to the quoted field issue, only the first record is parsed correctly

## Technical Details

### Files Structure
```
├── include/data.h          # Data structures and function declarations
├── src/api_fetching.c      # API fetching and CSV parsing functions
└── main.c                  # Test program
```

### Key Functions
- `fetch_api_data()` - Downloads CSV data using libcurl
- `parse_covid_csv()` - Parses CSV into data structures
- `create_covid_data()` - Memory allocation for data containers
- `free_covid_data()` - Proper memory cleanup

### Compilation
```bash
gcc -o covid_fetcher src/api_fetching.c main.c -lcurl
```

## Future Improvements (If Resumed)

- [ ] **Proper CSV Parser**: Implement RFC 4180 compliant CSV parsing
- [ ] **Quoted Field Handling**: Handle fields like `"City, State, Country"`
- [ ] **Escaped Character Support**: Handle `""` as escaped quotes
- [ ] **Better Error Recovery**: More robust parsing with malformed data
- [ ] **Performance Optimization**: Reduce memory allocations during parsing

## Why This Project Was Valuable

Even though discontinued, this project taught me:
- **Real-world API integration** in C
- **Memory management** best practices
- **The complexity of "simple" tasks** like CSV parsing
- **Proper error handling** and cleanup
- **Modular C programming** design patterns
