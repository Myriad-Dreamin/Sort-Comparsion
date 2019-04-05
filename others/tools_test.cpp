

#include <iostream>
#include "../test_src/collect.h"
#include "../src/tools.h"

int main() {
	FileHandle fha("./test.csv", std::ios::out | std::ios::app);
	FileHandle fhb("./test.csv", std::ios::out | std::ios::app);
	fha.block("fha_test");fha.block("fha_go");
	fha.newline();
	fhb.block("fhb_test");fhb.block("fhb_go");
	fhb.newline();
	fha.block("fha_test");fha.block("fha_go");
	fha.newline();
	fha.block(1);fha.block('A');
	fha.newline();
	fha.block(1.24);fha.block(15.5);
	fha.newline();

	fha.close();
	fhb.close();
}