# Description
This is the snake game for the purpose of collecting data on the game for AI training

# How to Run

## Run 10 Games

```bash
./games/worm.x > output.txt
```

## Run N Number of Games

```bash
./games/worm.x N > output.txt
```

# Useful Grep Commands

## Find all scores

```bash
grep -e "Score: [1-9][0-9]*" output.txt
```

## Find all scores + board values (Output might be big)

```bash
grep -A 11 -e "Score: [1-9][0-9]*" output.txt
```