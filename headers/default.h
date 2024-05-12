#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <memory>

using namespace std;

// overwriting common long types
using array = vector<int>;
using matrix = vector<vector<int>>;
using sentence = vector<string>;
// templates for better  inputs
template<typename T>
T input(T& data) {
	cin >> data;
	cin.clear();
	cin.ignore();
	return data;
}

template<typename T>
T input(const string& prompt, T& data) {
	cout << prompt;
	cin >> data;
	cin.clear();
	cin.ignore();
	return data;
}

template<typename T, typename... Args>
void input(const string& prompt, T& data, Args&... args) {
	cout << prompt;
	cin >> data;
	cin.clear();
	cin.ignore();
	input(args...);
}
// a different function for when multiple inputs are needed but without any prompts

void inputs(){}

template<typename T, typename... Args>
void inputs(T& data, Args&... args) {
	cin >> data;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	inputs(args...);
}

void log() {}

template<typename T, typename... Args>
void log(T data, Args... args) {
	cout << data << endl;
	log(args...);
}


template<typename T>
void log_vec(vector<T>& vec) {
	for (T entry : vec) {
		cout << " " << entry <<" ";
	}
}

template<typename T>
void log_vec(vector<T>& vec, string begin, string end) {
	for (T entry : vec) {
		cout << begin << entry << end;
	}
}

template<typename T>
void log_vec(vector<T>& vec, sentence custom_begin, string end) {
	size_t size = vec.size();
	if (custom_begin.size() != size)
	{
		cerr << "Custom beginning array has invalid size, it should have " << size << " elements";
		return;
	}
	size_t i = 0;
	for (T entry : vec) {
		cout << custom_begin[i++] << entry << end;
	}
}

template<typename T, typename... Args>
void push_log(ostream& outStream, T data, Args... args) {
	outStream << data << endl;
	push_log(outStream, args...);
}

template<typename T>
void push_log_vec(ostream& outStream, vector<T>& vec) {
	for (T entry : vec) {
		cout << " " << entry << " ";
	}
}

template<typename T>
void push_log_vec(ostream& outStream, vector<T>& vec, string begin, string end) {
	for (T entry : vec) {
		outStream << begin << entry << end;
	}
}

template<typename T>
string push_log_vec(ostream& outStream, vector<T>& vec, string end, sentence custom_begin) {
	size_t size = vec.size();
	if (custom_begin.size() != size)
	{
		cerr << "Custom beginning array has invalid size, it should have " << size << " elements";
		return "\0";
	}
	size_t i = 0;
	string	buffer;
	for (T entry : vec) {
		buffer.append(custom_begin[i++]);
		buffer.append(to_string(entry));
		buffer.append(end);
	}
	outStream << buffer;
	return buffer;
}
