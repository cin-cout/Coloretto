#include <iostream>  
#include <cstdlib>   
#include <iomanip>   
#include <ctime>     
#include <string>    
using namespace std; 



int  players = 1;            
int  draw_or_take = 0;      
int  pile_top = 1;          
char line_choice = 'f';     
int  r = 1;                 
bool f = 0;                
bool m = true;             
int player_now = 1;         
string board[4][6];         
int scores[6][10];          
int determination = 0;      
int dont_change_player = 0; 
string card_type[11] = { "無", "紅", "橙", "黃", "綠", "藍", "金", "銀", "彩", "加", "終" };

void board_show(void)
{
	cout << setw(5) << 'A' << setw(5) << 'B' << setw(5) << 'C';
	if (players >= 4) { cout << setw(5) << 'D'; }
	if (players >= 5) { cout << setw(5) << 'E'; }
	cout << endl;
	for (int s = 1; s <= 5 * (players + 1); s++) { cout << "-"; }
	cout << endl;
	for (int i = 1; i <= 3; i++)
	{
		for (int j = 1; j <= players; j++)
		{
			cout << setw(5) << board[i][j];
		}
		cout << endl;
	}
}
void cin_draw_or_take(void)
{
	if (dont_change_player == 0)
	{
		if (player_now == 1)
		{
			int u = 0;


			for (int i = 1; i <= players; i++)
			{
				if (board[1][i] != "無"&&board[1][i] != "禁") { u = 1; break; }
			}
			if (u == 1)
			{
				cout << "Please choose to draw the card(enter 1) or to take the row(enter 2).\n";
				cout << "Your decision:";
				cin >> draw_or_take;
				cout << endl;
			}
			if (u == 0)
			{
				cout << "Because there is no line to take,so you can only draw the card.\n";
				draw_or_take = 1;
			}
		}
		if (player_now != 1)
		{
			int e = 0;
			cout << "This is AI's turn .";


			draw_or_take = rand() % 2 + 1;
			cout << endl;

			for (int i = 1; i <= players; i++)
			{
				if (board[1][i] != "無"&&board[1][i] != "禁")
				{
					e = 1;
					break;
				}
				if (i == players && e == 0) { draw_or_take = 1; }
			}
			e = 0;
		}
	}
	if (dont_change_player == 1)
	{
		cout << "You change your mind to draw the card.\n";
		draw_or_take = 1;
		dont_change_player = 0;
	}
	if (draw_or_take == 1) { cout << "You decide to draw the card.\n"; }
	if (draw_or_take == 2) { cout << "You decide to take the row. \n"; }
}
void take_row_decision(void)
{
	bool qu = 0;

	do
	{
		cout << "Please decide which line to take.\n";
		board_show();
		if (player_now == 1)
		{
			cout << "The line you choose to take :";
			cin >> line_choice;
		}
		if (player_now != 1)
		{
			int line_choice_computer = 0;

			do {
				line_choice_computer = rand() % players + 1;
			} while (board[1][line_choice_computer] == "禁" || board[1][line_choice_computer] == "無");

			for (int i = 1; i <= 5; i++)
			{
				if (line_choice_computer == i) { line_choice = 'a' + (i - 1); }
			}

		}

		for (int i = 0; i <= players - 1; i++)
		{
			if (line_choice == 'A' + i || line_choice == 'a' + i) { qu = 1; }
		}

	} while (qu == 0);
	qu = 0;
}


void take_row_count(void)
{
	int line_choice_value;
	for (int i = 1; i <= 5; i++)
	{
		if (line_choice == 'A' + (i - 1) || line_choice == 'a' + (i - 1)) { line_choice_value = i; }
	}

	for (int r = 1; r <= 3; r++)
	{
		for (int i = 1; i <= 9; i++)
		{
			if (board[r][line_choice_value] == card_type[i]) { scores[player_now][i]++; continue; }
		}
	}
}
void take_row_flow_universe(void)
{
	int jump = 0;
	for (int p = 0; p <= players - 1; p++)
	{


		if (line_choice == 'A' + p || line_choice == 'a' + p)
		{

			if (board[1][p + 1] != "無"&&board[1][p + 1] != "禁")
			{
				take_row_count();
				for (int x = 1; x <= 3; x++)
				{
					board[x][p + 1] = "禁";
				}
				board[0][player_now] = "關";

			}
			else if (board[1][p + 1] == "禁")
			{
				cout << "The line cannot be choosed before all line will have been choosed.\n";
				take_row_decision();
				take_row_flow_universe();
				p = players;
			}
			else
			{
				cout << "There is no card on the line , please take another line or choose to draw.\n";
				cout << "If you change your mind to draw the card,please enter 1.\n";
				cout << "Your decision:";
				cin >> jump;
				cout << "\n";
				if (jump == 1) { dont_change_player = 1; break; }
				if (jump != 1)
				{
					line_choice = 'f';
					take_row_decision();
					take_row_flow_universe();
					p = players;
				}

			}
		}
	}


	jump = 0;

}

void scores_initiallization(void)
{
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 9; j++)
		{
			scores[i][j] = 0;
		}

	}
}
void scores_table_show(void)
{
	if (f == 0) { cout << setw(10) << "紅" << setw(7) << "橙" << setw(7) << "黃" << setw(7) << "綠" << setw(7) << "藍" << setw(7) << "金" << setw(7) << "銀" << setw(7) << "彩" << setw(7) << "加" << endl; }
	if (f == 1)
	{
		cout << "After count the number of each kind of cards , we show according to the order.\n";
		cout << setw(10) << "一" << setw(7) << "二" << setw(7) << "三" << setw(7) << "四" << setw(7) << "五" << setw(7) << "六" << setw(7) << "七" << setw(7) << "彩" << setw(7) << "加" << endl;
	}
	for (int i = 1; i <= players; i++)
	{
		cout << i << " |" << setw(5);
		for (int j = 1; j <= 9; j++)
		{
			cout << setw(7) << scores[i][j];
		}
		cout << endl;
	}
	cout << endl;
}
void board_initiallization(void)
{
	for (int i = 0; i <= 3; i++)
	{
		for (int j = 0; j <= 5; j++)
		{
			board[i][j] = "無";
		}

	}
}

void from_low_to_high(void)
{
	for (int i = 1; i <= players; i++)
	{

		for (int m = 1; m <= 7; m++)
		{

			int moving_copy = scores[i][m];
			int now_object = m;
			while ((now_object < 7) && (moving_copy > scores[i][now_object + 1]))
			{
				scores[i][now_object] = scores[i][now_object + 1];
				now_object++;
			}
			scores[i][now_object] = moving_copy;
		}
	}
}
void from_high_to_low(void)
{
	int round_most = 0;
	int p = 0;
	for (int i = 1; i <= players; i++)
	{

		for (int m = 1; m <= 7; m++)
		{
			round_most = scores[i][7];
			for (int k = 7; k >= m + 1; k--)
			{
				if (scores[i][k] < scores[i][k - 1])
				{
					round_most = scores[i][k - 1];
				}
			}
			p = 0;
			for (int q = m; q <= 7; q++)
			{
				if (round_most == scores[i][q]) { p = q; break; }
			}
			for (int w = p - 1; w >= m; w--)
			{
				scores[i][w + 1] = scores[i][w];
			}
			scores[i][m] = round_most;
		}
		round_most = 0;
		p = 0;
	}
}
void player_now_determination(void)
{
	for (int i = 1; i <= players; i++)
	{
		if (board[0][i] != "關") { determination = 1; break; }
	}
	if (determination == 1)
	{
		do
		{
			player_now++;
			if (player_now == players + 1) { player_now = 1; }
		} while (board[0][player_now] == "關");
	}
	determination = 0;
}
void final_point(void)
{
	for (int p = 1; p <= players; p++)
	{
		for (int i = 1; i <= 3; i++)
		{
			if (scores[p][i] < 6)
			{
				while (scores[p][8] > 0 && scores[p][i] < 6)
				{
					scores[p][i]++;
					scores[p][8]--;
				}
			}
		}
		for (int i = 7; i >= 4; i--)
		{
			if (scores[p][i] < 6)
			{
				while (scores[p][8] > 0 && scores[p][i] < 6)
				{
					scores[p][i]++;
					scores[p][8]--;
				}
			}
		}

		for (int i = 1; i <= 3; i++)
		{
			if (scores[p][i] == 6) { scores[p][0] += 21; }
			if (scores[p][i] == 5) { scores[p][0] += 15; }
			if (scores[p][i] == 4) { scores[p][0] += 10; }
			if (scores[p][i] == 3) { scores[p][0] += 6; }
			if (scores[p][i] == 2) { scores[p][0] += 3; }
			if (scores[p][i] == 1) { scores[p][0] += 1; }

		}
		for (int i = 4; i <= 7; i++)
		{
			if (scores[p][i] == 6) { scores[p][0] -= 21; }
			if (scores[p][i] == 5) { scores[p][0] -= 15; }
			if (scores[p][i] == 4) { scores[p][0] -= 10; }
			if (scores[p][i] == 3) { scores[p][0] -= 6; }
			if (scores[p][i] == 2) { scores[p][0] -= 3; }
			if (scores[p][i] == 1) { scores[p][0] -= 1; }
		}
		scores[p][0] += scores[p][9] * 2;
	}
}

void final_point_print(void)
{
	cout << "\n\n";
	for (int i = 1; i <= 5; i++)
	{
		cout << i << "|" << scores[i][0] << "\n";
	}
	cout << "\n\n";
}
void winner_determination_and_show(void)
{
	int point_most;
	point_most = scores[1][0];
	for (int i = 2; i <= players; i++)
	{
		if (scores[i][0] > scores[1][0]) { point_most = scores[i][0]; }
	}

	for (int i = 1; i <= players; i++)
	{
		if (scores[i][0] == point_most) { cout << "The winner is player " << i << ".\n"; }
	}
}


int  main()
{
	scores_initiallization();                                                                 


	cout << "Welcome to the Coloretto Game.\n\n";                                             
	cout << "Please decide the number of players [one is you,and the other(s) is AI]\n";      
	cout << "It is restricted to play by 3~5 people,so don't enter other number of people.\n";

	while (players < 3 || players>5)                                                          
	{
		cout << "The number of players :";
		cin >> players;
		cout << endl;

		if (3 <= players && players <= 5) { cout << "Please decide the level of AI\n"; }      
		else {
			cout << "Error: Please enter a number between 3~5\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

	}

	srand((unsigned)time(NULL));                                                             
	string card[78];                                                                          
	for (int q = 0; q <= 77; q++) { card[q] = "無"; }                                         
	card[62] = "終";                                                                          
	int k;                                                                                    
	for (int u = 0; u <= 6; u++)                                                              
	{
		for (int i = 1; i <= 9; i++)                                                          
		{
			k = rand() % 77 + 1;                                                              
			if (card[k] == "無")                                                              
			{
				switch (u)                                                                  
				{
				case 0:  card[k] = "紅"; break;
				case 1:  card[k] = "橙"; break;
				case 2:  card[k] = "黃"; break;
				case 3:  card[k] = "綠"; break;
				case 4:  card[k] = "藍"; break;
				case 5:  card[k] = "金"; break;
				case 6:  card[k] = "銀"; break;
				default: break;                                                               
				}
				i++;                                                                          
			}
			i--;                                                                              
		}
	}
	for (int i = 1; i <= 3; i++)                                                              
	{
		k = rand() % 77 + 1;
		if (card[k] == "無")
		{
			card[k] = "彩";
			i++;
		}
		i--;
	}
	for (int i = 1; i <= 10; i++)                                                            
	{
		k = rand() % 77 + 1;
		if (card[k] == "無")
		{
			card[k] = "加";
			i++;
		}
		i--;
	}

	for (int i = 1; i <= players; i++)                                                       
	{
		do
		{
			k = rand() % 77 + 1;
			for (int j = 1; j <= 7; j++)
			{
				if (card[k] == card_type[j]) { scores[i][j]++; card[k] = "無"; break; }
			}

		} while (card[k] == "彩" || card[k] == "加" || card[k] == "終");
	}

	for (int i = 63; i <= 77; i++)                                                           
	{
		if (card[i] == "無")
		{
			do
			{
				k = rand() % 62 + 1;
			} while (card[k] == "無");
			card[i] = card[k];
			card[k] = "無";
		}
	}

	scores_table_show();                                                                      
	board_initiallization();                                                                  

	for (int j = 1; j <= 77; j++)                                                            
	{
		cout << card[j] << "  ";
		if (j % 10 == 0) { cout << endl; }
	}

	cout << endl << endl;                                                                    

	while (true)                                                                             
	{
		if (f == 0) { cout << "Now is player " << player_now << "'s turn." << "\n\n"; }      

		

		bool qu = 0;                                                               
		for (int i = 1; i <= players; i++)                                               
		{
			if (board[3][i] != "禁") { qu = 1; break; }
		}

		if (qu == 0)                                                                       
		{
			if (f == 0)                                                                  
			{
				cout << "Because all line have been taken , so the board is initialized.\n";
				board_initiallization();

				board_show();
			}
			if (f == 1)                                                                  
			{
				cout << "The final round is over , the computer will count the final point of this game.\n";
				break;
			}
		}

		qu = 0;                                                                            
		for (int i = 1; i <= players; i++)                                               
		{
			if (board[3][i] == "無") { qu = 1; break; }
		}

		if (qu == 1)                                                                       
		{
			while (draw_or_take != 1 && draw_or_take != 2)
			{
				cin_draw_or_take();
				dont_change_player = 0;

			}
		}
		else if (qu == 0)                                                                 
		{
			cout << "Because there is no space to place the card , so you only can decide which line to take.\n";
			draw_or_take = 2;
		}
		qu = 0;                                                                          


		if (draw_or_take == 1)
		{
			if (card[pile_top] == "終")                                                                 
			{
				cout << "You draw the final round card , so the game will be over after this round .\n";
				cout << "You get the next card to place.\n";                                            
				pile_top++;                                                                             
				f = 1;                                                                                  
				system("pause");                                                                        
			}
			if (card[pile_top] == "無") { pile_top++; }                                                 

			cout << "The new-drawed card is " << "\"" << card[pile_top] << "\"" << endl << endl;             
			cout << "Please decide which line to place.\n";                                           
			board_show();                                                                              



			while (r == 1)
			{
				while (m == true)                                                                       
				{
					if (player_now == 1)                                                                
					{
						cout << "The line you choose to place :";
						cin >> line_choice;
					}
					if (player_now != 1)                                                              
					{
						int line_choice_computer = 0;                                                     
						do {
							line_choice_computer = rand() % players + 1;
						} while (board[1][line_choice_computer] == "禁" || board[3][line_choice_computer] != "無");

						for (int i = 1; i <= 5; i++)                                                               
						{
							if (line_choice_computer == i) { line_choice = 'a' + (i - 1); }
						}

					}

					for (int i = 0; i <= players - 1; i++)                                                            
					{
						if (line_choice == 'A' + i || line_choice == 'a' + i) { qu = 1; break; }
					}
					if (qu == 0) { m = true; }
					else if (qu == 1) { m = false; }
					qu = 0;                                                                                          

				}
				for (int k = 0; k <= players - 1; k++)                                                                  
				{
					if (line_choice == 'A' + k || line_choice == 'a' + k)
					{
						if (board[1][k + 1] != "禁")                                                                  
						{
							for (int i = 1; i <= 3; i++)                                                              
							{
								if (board[i][k + 1] == "無")                                                          
								{

									board[i][k + 1] = card[pile_top];                                                 
									pile_top++;                                                                       
									r = 0;                                                                            
									break;                                                                            
								}
								else if (board[3][k + 1] != "無")                                                          
								{
									r = 1;                                                                            
									m = true;                                                                         
									cout << "The line is full ,please put at another line.";                          
									break;
								}
							}
						}
						else                                                                                          
						{
							cout << "The line cannot be choosed before all line will have been choosed.\n";           
							r = 1;                                                                                    
							m = true;                                                                                 
						}
					}

				}

			}


			board_show();             
			cout << "\n";              

			draw_or_take = 0;         
			r = 1;                    
			line_choice = 'f';         
			m = true;                  

			if (player_now == 1)
			{
				cout << "This the the decision result of you ,and the program pause for you to check your behavior.\n";
				system("pause");
			}

			player_now_determination();

			if (player_now == 1)       
			{
				cout << "This the the scores board now ,and the program pause for you to check it.\n";
				scores_table_show();   
				cout << "\n";          
				system("pause");

			}

			if (pile_top == 78) 
			{
				f = 1;
				cout << "The card is used out , so the computer will count the final point later.\n";
				break;
			}
		}

		if (draw_or_take == 2)        
		{
			take_row_decision();       

			take_row_flow_universe();  

			board_show();              
			cout << "\n";

			draw_or_take = 0;                                           
			line_choice = 'f';                                         

			if (player_now == 1)
			{
				cout << "This the the decision result of you ,and the program pause for you to check your behavior.\n";
				system("pause");
			}

			if (dont_change_player != 1) { player_now_determination(); }

			if (player_now == 1)       
			{
				cout << "This the the scores board now ,and the program pause for you to check it.\n";
				scores_table_show();   
				cout << "\n";          
				system("pause");
			}

		}




		for (int i = 1; i <= players; i++)
		{
			scores[i][0] = 0;
		}


	}

	if (f == 1)
	{
		from_high_to_low();
		scores_table_show();
		final_point();
		final_point_print();
		winner_determination_and_show();
	}

	system("pause");
	return 0;
}

