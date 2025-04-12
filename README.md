This repository is no longer being maintained.
ArcPlusInventory was originally designed as an extension to the ArcInventory plugin, which is a paid product owned by another developer. Since its usefulness is limited to those who have purchased ArcInventory, I've decided to retire this project.

Going forward, I'm focusing my efforts on building [RockInventory](https://github.com/brokenrockstudios/RockInventory) — a fully standalone, free, and open-source inventory system. It’s designed from the ground up to be flexible, performant, and independent of any third-party dependencies.




# ArcPlusInventory

An opinionated extension of ArcInventory.

## Overview
This plugins is intended to extend ArcInventory in places that ArcInventory wants to stay generalizable and minimum opinion. This plugin will be filled with opinionated decisions. 

The inspiration draws from inventory systems functionality found in popular games like Diablo and Escape From Tarkov, where items can occupy different numbers of grid slots based on their size and shape.

## Purpose
This extension leverages ArcInventory's robust backend architecture (which utilizes a system similar to Lyra's fragment system) to implement a more flexible inventory solution for games requiring sophisticated item management.


## Features

* Support for items of various dimensions (1x1, 1x2, 2x2, 2x3, etc.)
* Grid-based collision detection for item placement
* Visual representation of variable-sized items in inventory UI
* Integration with ArcInventory's existing fragment-based architecture


## License

The code in this repo is licensed under the MIT License. 

This plugin is an extension of ArcInventory and therefore any core ArcInventory is subject to it's own licensing.


## Dependencies

[ArcInventory](https://www.fab.com/listings/ee4027dd-0a9f-4ac9-a7e6-78994f67c133) has a solid backend inspired similiar to Lyra's fragment system. 


## Special Thanks:

* namrog84
* Wupy36
* ArcInventory Creators (RoyAwesome and PunyHuman)


