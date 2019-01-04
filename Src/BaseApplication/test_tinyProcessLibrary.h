#pragma once

#include "process.hpp"

#include <iostream>

using namespace std;
using namespace TinyProcessLib;


void test_process_tiny_lib()
{
	cout << "Example 1 - the mandatory Hello World" << endl;
	Process process1("cmd /C echo Hello World", "", [](const char *bytes, size_t n) {
		cout << "Output from stdout: " << string(bytes, n);
	});
	auto exit_status = process1.get_exit_status();
	cout << "Example 1 process returned: " << exit_status << " (" << (exit_status == 0 ? "success" : "failure") << ")" << endl;
	this_thread::sleep_for(chrono::seconds(5));
	
	cout << endl << "Example 2 - cd into a nonexistent directory" << endl;
	Process process2("cmd /C cd a_nonexistent_directory", "", [](const char *bytes, size_t n) {
		cout << "Output from stdout: " << string(bytes, n);
	}, [](const char *bytes, size_t n) {
		cout << "Output from stderr: " << string(bytes, n);
		//add a newline for prettier output on some platforms:
		if (bytes[n - 1] != '\n')
			cout << endl;
	});
	exit_status = process2.get_exit_status();
	cout << "Example 2 process returned: " << exit_status << " (" << (exit_status == 0 ? "success" : "failure") << ")" << endl;
	this_thread::sleep_for(chrono::seconds(5));


	cout << endl << "Example 3 - async sleep process" << endl;
	thread thread3([]() {
		Process process3("timeout 5");
		auto exit_status = process3.get_exit_status();
		cout << "Example 3 process returned: " << exit_status << " (" << (exit_status == 0 ? "success" : "failure") << ")" << endl;
	});
	thread3.detach();
	this_thread::sleep_for(chrono::seconds(10));


	cout << endl << "Example 4 - killing async sleep process after 5 seconds" << endl;
	auto process4 = make_shared<Process>("timeout 10");
	thread thread4([process4]() {
		auto exit_status = process4->get_exit_status();
		cout << "Example 4 process returned: " << exit_status << " (" << (exit_status == 0 ? "success" : "failure") << ")" << endl;
	});
	thread4.detach();
	this_thread::sleep_for(chrono::seconds(5));
	process4->kill();
	this_thread::sleep_for(chrono::seconds(5));


	cout << endl << "Example 5 - demonstrates Process::try_get_exit_status" << endl;
	Process process5("timeout 5");
	while (!process5.try_get_exit_status(exit_status)) {
		cout << "Example 5 process is running" << endl;
		this_thread::sleep_for(chrono::seconds(2));
	}
	cout << "Example 5 process returned: " << exit_status << " (" << (exit_status == 0 ? "success" : "failure") << ")" << endl;
}