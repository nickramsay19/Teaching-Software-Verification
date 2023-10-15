#!/bin/bash

sudo docker build --build-arg test="$1" .
