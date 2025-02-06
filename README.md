# 📜 get_next_line

A **C programming project** that implements the function `get_next_line`, which **reads a line from a file descriptor** efficiently.

---

## 🚀 Features
✅ Reads a **single line** from a file descriptor (**fd**) at a time.
✅ Efficient **buffered reading** for performance.
✅ Works with **any file**, including standard input (**stdin**).
✅ Handles **multiple file descriptors** simultaneously.

---

## 🛠 Installation & Usage

### 1️⃣ Clone the Repository
```sh
git clone https://github.com/AlenasRed/get_next_line.git
cd get_next_line
```

### 2️⃣ Compile the Program
Use `gcc` to compile:
```sh
gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl
```

### 3️⃣ Run the Program
```sh
./gnl file.txt
```

---

## 📂 Project Structure
```
/get_next_line
├── get_next_line.c       # Core function implementation
├── get_next_line.h       # Header file
├── get_next_line_utils.c # Helper functions
├── main.c                # Example usage (for testing)
├── README.md             # Documentation
```

---

## 📌 Function Prototype
```c
char *get_next_line(int fd);
```

- **fd**: File descriptor to read from.
- Returns the next **line** read, or **NULL** if EOF is reached or an error occurs.

---

## ⚙️ How It Works
1. Reads from the file descriptor **incrementally** using a buffer.
2. Stores any **leftover characters** for the next function call.
3. Returns a **dynamically allocated string** containing the next line.

---

## 🔥 Example Usage
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main() {
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd))) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

---

## 🛠 Configuration
You can change the **buffer size** by modifying `BUFFER_SIZE` in compilation:
```sh
gcc -D BUFFER_SIZE=128 get_next_line.c get_next_line_utils.c main.c -o gnl
```

---

## 📜 License
This project is **open-source** and free to use under the MIT License.

🎉 **Happy Coding!** 🚀

