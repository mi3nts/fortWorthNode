#!/bin/bash

sleep 5
python3 centralNodeReaderDue.py &
sleep 5
python3 centralNodeReaderNano.py &
sleep 10 
cd odroidShow2 && python3 mintsShow2.py
