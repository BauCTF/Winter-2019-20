# C Warrior

This is a game designed to teach the C language and artificial intelligence in a fun, interactive way.

You play as a warrior climbing a tall tower to save a _prinCess_ at the top level. On each floor you need to write a C script to instruct the warrior to battle enemies, rescue captives, and reach the stairs. You have some idea of what each floor contains, but you never know for certain what will happen. You must give the Warrior enough artificial intelligence up-front to find his own way.

## Getting Started

### Prerequisites

GNU Compiler Collection (GCC)

- Linux

```
sudo apt install gcc
```

- MacOs

```
brew install gcc
```

- Others [GCC website](https://gcc.gnu.org/install/binaries.html)

Assign execute permission to run.sh (for Linux and MacOs)

```
chmod +x run.sh
```

### How to Play !

run the following command

- Terminal

```
./run.sh
```

- CMD

```
run
```

Choose a Tower and then setup your profile.
This will create a profile directory in your current location where you can see `Play.c` that contains :

```
void playTurn(Warrior *warrior)
{
    // your code goes here
}

```

Your objective is to fill this `playTurn` function with commands to instruct the warrior what to do. With each level your abilities will grow along with the difficulty. See the `README.md` in profile's directory for details on what abilities your warrior has available on the current level.

Here is a simple example which will instruct the warrior to walk forward.

```
void playTurn(Warrior *warrior)
{
    warrior->walk();
}

```

Once you are done editing `Play.c`, save the file and run the `run.sh` again to start playing the level. The play happens through a series of turns. On each one, your `playTurn` function is called along with any enemy's.

You cannot change your code in the middle of a level. You must take into account everything that may happen on that level and give your warrior the proper instructions from the start.

Losing all of your health will cause you to fail the level. You are not punished by this, you simply need to go back to your `Play.c`, improve your code, and try again.

Once you pass a level (by reaching the stairs), the profile `README.md` will be updated for the next level. Alter the `Play.c` file and run `run.sh` again to play the next level.

## Commands

### Actions

```
warrior->walk()
  Move in given direction (forward by default).

warrior->attack()
  Attack the unit in given direction (forward by default).

warrior->rest()
  Gain 10% of max health back, but do nothing more.

```

### Sense

```
warrior->feel
  Returns a Space for the given direction (forward by default).

warrior->health()
  Returns an integer representing your health.

warrior->maxHealth()
  Returns an integer representing your health.

```

### Feel

```
feel->empty()
  If true, this means that nothing (except maybe stairs) is at this location and you can walk here.

```

## Authors

- **Parsa Samadnejad** - _Initial work_

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

## Acknowledgments

- Credits for the original idea go to [Ryan Bates](https://github.com/ryanb) - [ruby-warrior](https://github.com/ryanb/ruby-warrior).
- Inspired By [warriorjs](https://github.com/olistic/warriorjs) - [Matías Olivera](https://github.com/olistic)
