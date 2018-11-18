#!/bin/bash

javac *.java
java ChatServer 5002 &
gnome-terminal -x java IHM &
gnome-terminal -x java IHM
