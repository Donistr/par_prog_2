import argparse
import numpy as np
import json


parser = argparse.ArgumentParser()
parser.add_argument("matricies1", type=str, help="первые матрицы")
parser.add_argument("matricies2", type=str, help="вторые матрицы")
parser.add_argument("matriciesRes", type=str, help="результирующие матрица")
args = parser.parse_args()

with open(args.matricies1, "r") as file:
    matricies1 = np.array(json.loads(file.read()))
with open(args.matricies2, "r") as file:
    matricies2 = np.array(json.loads(file.read()))
with open(args.matriciesRes, "r") as file:
    matriciesRes = np.array(json.loads(file.read()))
for i in range(matricies1.size):
    matrix1 = matricies1[i]["matrix"]
    matrix2 = matricies2[i]["matrix"]
    res = matriciesRes[i]["matrix"]
    if not np.array_equal(res, np.dot(matrix1, matrix2)):
        print("Error")
