import pyperclip
import time

d = {'\n\n': '\n', '$': '', r' \le ': ' ≤ ', r' \ge ': ' ≥ ', r' \leq ': ' ≤ ', r'\dots': '...', r'\ldots': '...', r'\rightarrow': '→',
     r'\to': '→', r'\leftarrow': '←', r' \cdot ': '*', r' \ne ': '≠', r'\oplus': '⊕'}


def main():
    while True:
        t = pyperclip.paste()
        for key in d:
            t = t.replace(key, d[key])
        pyperclip.copy(t)
        time.sleep(0.1)


if __name__ == "__main__":
    main()
