@echo off
python generate.py >keywords.h
copy keywords.h ..\MicroBASICConsole
