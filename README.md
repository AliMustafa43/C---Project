# 🛡️ C++ Cryptography Toolkit

A robust command-line utility for data encryption. This project was developed as a technical challenge to explore low-level memory management and professional-grade software architecture in C++.

---

## 💡 About This Project
This toolkit was built with the assistance of AI to bridge the gap between classroom theory and industry-standard coding practices. 
My goal was to study how advanced concepts like **pointer arithmetic** and **persistent file handling** are implemented in a real-world scenario.

---

## 🚀 Key Features

* **Pointer-Based Logic:** High-performance memory manipulation using pointer arithmetic for string traversal.
* **Persistent Audit Logging:** Automatic history tracking saved to `crypto_history.log` for session review.
* **Robust Input Validation:** Engineered to handle invalid user data without crashing.
* **Dual-Mode Operation:** Full support for both **Encryption** and **Decryption**.

---

## 🛠️ Ciphers Included

1.  **Caesar Cipher:** Substitution using pointer-based memory shifting.
2.  **Atbash Cipher:** Symmetric alphabet mirroring logic.
3.  **Vigenère Cipher:** Polyalphabetic substitution using secret keywords.
4.  **Rail Fence Cipher:** Transposition technique using zigzag pattern logic.

---

## ⚙️ How to Run

### Online Demo (Interactive)
[Try the interactive demo here](https://www.jdoodle.com/ia/1SxS)

### Local Machine
1. **Clone the repository:**
   ```bash
   git clone [https://github.com/AliMustafa43/Cryptography_Toolkit.git](https://github.com/AliMustafa43/Cryptography_Toolkit.git)
   cd Cryptography_Toolkit

### Local Machine
1. Clone the repository:
git clone https://github.com/AliMustafa43/Cryptography_Toolkit.git
cd Cryptography_Toolkit
g++ main.cpp -o toolkit
./toolkit

📄 Note on Logging
The history tracking feature generates a crypto_history.log file. 
While testing via the online Replit demo, this file is temporary and cleared after each session. 
To maintain a permanent audit trail, please clone the repository and run the project in a local environment.
