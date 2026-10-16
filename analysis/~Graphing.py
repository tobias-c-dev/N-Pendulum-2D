#!/usr/bin/python3

import pandas as pd 

data = pd.read_csv("../data/pendulum.csv")

print(data.head())
print(data.columns[:],[2])