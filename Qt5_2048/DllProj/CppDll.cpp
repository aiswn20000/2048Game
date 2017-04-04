/* ��� ������ ��� ������� ������ state, ��� ������ ������� � ������� ����������� ������.
*  �� ����, ��� ������ ��������������� � dll ��� x86, � ���������� ���������� ���� ��������� 
*  ���������� �� C#
*/


#include <string>
#include <sstream>
#include <iterator>
#include "..\state.h"
#include "stdafx.h"

namespace Solver {

	class driver {
		std::string name;
		char * rawData;
		int size;
		int depth;
		solver sage;
		state initial_state;

	public:
		//  ����������� ��������� ��������� ��������� � ��������� ����� �������
		driver(std::string className, char * data, int length, int searchDepth) : name(className), depth(searchDepth), sage(searchDepth), initial_state(data, length)
		{
			sage.solveAlphaBeta(initial_state);
		}

		//  ��� ������ ������������ ������ � ���� � ���� ������ ���������. ������������, �� �� ��������� � ������� �� �����
		int exportData(char * buffer, int buffSize, int * score)
		{
			//  ����������� ��� ��� ������� (� ������������ ������ �����, ������ ������ ������ �������� "������"
			state final_state(initial_state);
			std::array<int, cellCount> dummy1, dummy2;
			moves best_move = sage.proposedMove();
			int moveScore = 0;

			final_state.performSlide(best_move, dummy1, dummy2, moveScore);
			final_state.exportField(buffer, buffSize);

			*score = moveScore;

			switch (best_move) {
				case moves::up: return 1;
				case moves::right: return 2;
				case moves::down: return 3;
				case moves::left: return 4;
			}

			return 0;
		}
	};

	extern "C" __declspec(dllexport) int solveState(char *buffer, int buffSize, int depth, int * score)
	{
		return driver("Simple", buffer, buffSize, depth).exportData(buffer, buffSize, score);
	}

	/*extern "C" __declspec(dllexport) int summ(int a, int b)
	{
		return a + b;
	}
	
	extern "C" __declspec(dllexport) int sumDiff(int a, int b, int * sum, int * diff)
	{
		*sum = a + b;
		*diff = a - b;
		return 1;
	}

	extern "C" __declspec(dllexport) int allParamTest(char *buffer, int buffSize, int depth, int * score)
	{
		*score = depth * 4;

		for (char * cPtr = buffer; cPtr <= buffer + buffSize; ++cPtr)
			*cPtr = *cPtr + 3;

		return 2;
	}*/
}
