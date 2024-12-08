# Description
This is the snake game for the purpose of collecting data on the game for AI training

# How to Run

```bash
worm.x > output.txt
```

# Useful grep commands

Find all scores:

```bash
grep -e "Score: [1-9][0-9]*" output.txt
```

Find all scores + board values:

```bash
grep -A 11 -e "Score: [1-9][0-9]*" output.txt
```