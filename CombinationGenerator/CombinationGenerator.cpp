// CombinationGenerator.cpp : Defines the entry point for the console application.
/*
Given a set of candidate numbers (C) and a target number (T), find all unique combinations in C where the candidate numbers sums to T.
	1. The same repeated number may be chosen from C unlimited number of times.
	2. Each number in C may only be used once in the combination.
*/
//ALGO:
/*
1. For multple repeat of the same number:
We treat the duplicate num as one only and then start repeating the same num in possible solution while reducing the target sum

2. For unqiure combo:
	We identify the duplicate instances (N) of curr num. IN the solution vector, we generate solution while repeatinbg this
		curr num from 0 to N times and then directly jumping on to next number.
*/


#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void combination_generator_util_Unique(int i, int pendingSum, vector<int> &curr_sol, vector<vector<int> > &sol_set, vector<int> &A)
{
	if (pendingSum == 0)
	{
		//We have found the required combination...add it to sol_set
		sol_set.push_back(curr_sol);
		return;
	}

	//consider the ith element
	if (i == A.size() || pendingSum < 0) //No more element left for consideration
	{
		return;
	}

	//Identify the current set of dupicate elements
	int endIdx;
	for (endIdx = i + 1; endIdx < A.size() && A[endIdx] == A[endIdx - 1]; endIdx++)
	{

	}
	int currNumRepeat = endIdx - i;
	for (int p = 0; p <= currNumRepeat; p++)
	{
		//keep the curr num P time in the solution vector
		for (int q = 0; q < p; q++)
		{
			curr_sol.push_back(A[i]);
		}
		pendingSum -= p*A[i];
		combination_generator_util_Unique(endIdx, pendingSum, curr_sol, sol_set, A);
		pendingSum += p*A[i];
		for (int q = 1; q <= p; q++)
		{
			curr_sol.pop_back();
		}
	}
}

void combination_generator_util(int i, int pendingSum, vector<int> &curr_sol, vector<vector<int> > &sol_set, vector<int> &A)
{
	if (pendingSum == 0)
	{
		//We have found the required combination...add it to sol_set
		sol_set.push_back(curr_sol);
		return;
	}

	//consider the ith element
	if (i == A.size() || pendingSum < 0) //No more element left for consideration
	{
		return;
	}

	//Either consider ith element into curr sol_set
	//Avoid duplicately considering the same num
	while (i > 0 && A[i] == A[i - 1])
	{
		i++;
		if (i == A.size()) return;
	}
	curr_sol.push_back(A[i]);
	//here notice we are again considering ith elemenet only...as the same number can be repeated multiple times
	combination_generator_util(i, pendingSum - A[i], curr_sol, sol_set, A);

	//or don't consider ith element
	curr_sol.pop_back();
	combination_generator_util(i + 1, pendingSum, curr_sol, sol_set, A);
}

void generate_combintaion(vector<int> &A, int TargetSum, vector<vector<int> > &sol_set)
{
	sort(A.begin(), A.end());
	vector<int> curr_sol;

	combination_generator_util(0, TargetSum, curr_sol, sol_set, A);
}

void generate_combintaion_2(vector<int> &A, int TargetSum, vector<vector<int> > &sol_set)
{
	sort(A.begin(), A.end());
	vector<int> curr_sol;

	combination_generator_util_Unique(0, TargetSum, curr_sol, sol_set, A);
}

void print_solution(vector<vector<int> > &sol_set)
{
	for (int i = 0; i < sol_set.size(); i++)
	{
		cout << "{";
		for (int j = 0; j < sol_set[i].size(); j++)
		{
			cout << sol_set[i][j] << ", ";
		}
		cout << "}" << endl;
	}
}

int main()
{
	int N;
	cin >> N;
	vector<int> A(N);
	for (int i = 0; i < N; i++)
	{
		cin >> A[i];
	}
	int T; //target sum
	cin >> T;

	vector<vector<int> > sol_set, sol_set2;
	generate_combintaion(A, T, sol_set);

	print_solution(sol_set);

	cout << "ALL UNIQUE COMBO" << endl;
	generate_combintaion_2(A, T, sol_set2);
	print_solution(sol_set2);
	
    return 0;
}

