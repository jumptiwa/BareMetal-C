# BareMetal-C

Writing C directly to the hardware!
- **URL:** <https://github.com/kongkrit/BareMetal-C>
- **Purpose:** Repository for teaching/learning `BareMetal-C`
- **Go to [Setup Documents](#setup-documents)**

<p align="center">
  <img src="./docs-extra/bmc-1024.jpg" width="400">
</p>

---

## Setup Documents

These are the instructions to follow to set up your computer to be ready to do assignments.

You need to follow *all the steps* from 1-4 to have a working environment for the class:

1. Setup Tools - [instructions](./setup/1-setup-tools.md).
2. Setup `SimulIDE` - [instructions](./setup/2-setup-simulide.md).
3. Setup `Visual Studio Code` (`VS Code`) - [instructions](./setup/3-setup-vs-code.md).
4. Test the whole system - [instructions](./setup/4-setup-test.md).

Your environment should be ready.

---
  
>  **Warning:** Only perform instructions below if you have problems with `Docker Desktop` or `VS Code`.
>  It will erase all your Docker `images` and reset your VS Code `settings` and `extensions`. It will not touch anything else. Your personal data files should remain safe.
>
>  But we cannot guarantee that. So, **If you follow the *Reset* instructions below, *proceed at your own risk*.**
> 
>  - Reset Docker and VS Code to original state. See [instructions](./setup/5-reset-system.md)

---

## Lecture Notes

- Download lecture notes from <https://github.com/kongkrit/BareMetal-C/tree/main/slides>.
- Right now, the following lecture notes are available. More will be available soon:

  - [x] 00 Intro
  - [x] 01 Welcome to the Digital World
  - [ ] 02 From Text to Machine
  - [ ] 03 ...
  - [ ] 04 ...
---

## Reference Documents

These are the reference documents for the class:

- [x] 1. Read `C99 Coding Guildlines` [here](./docs-students/C99-coding-guidelines.md)
- [x] 2. Read `C99 Style Guide` [here](./docs-students/C99-style-guide.md)
- [x] 3. Read `C99 Operator Precedence` [here](./docs-students/C99-operator-precedence.md)
- [ ] 4. Cheat sheet

---

## Peripherals designed
- [x] 0xC000-0xC003 toggle switches
- [x] 0xE000-0xE003 LEDs
- [x] 0xE010-0xE017 strip LEDs
- [ ] numerical keypad read2clr
- [ ] directional keypad read2clr
