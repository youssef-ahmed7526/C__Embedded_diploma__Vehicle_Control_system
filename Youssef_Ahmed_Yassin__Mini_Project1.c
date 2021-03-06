#include <stdio.h>
#include <ctype.h>

#define WITH_ENGINE_TEMP_CONTROLLER 1

//functions' prototype:
void choose_system_state();
void Sensors_set_menu();
void traffic_light_color();
void room_temperature();
#if (WITH_ENGINE_TEMP_CONTROLLER)
void engine_temperature();
#endif
void display_state();

//defining vehicle parameters
int vehicle_speed=30;float Troom=35;
char engine_state=0,AC=0;
#if (WITH_ENGINE_TEMP_CONTROLLER)
float Tengine=90;
char ETC=0;
#endif

//main options to determine system state at the beginning of the program
void choose_system_state(){
	printf("\nWould you like to:\n");
	printf("a. Turn on the vehicle engine\n");
	printf("b. Turn off the vehicle engine\n");
	printf("c. Quit the system\n");
	char input;
	do
	{
		printf("please enter a,b or c: ");
		scanf(" %c",&input);
		input=tolower(input);
	} while (input!='a'&&input!='b'&&input!='c');
	switch(input)
	{
	case 'a':
		printf("\nTurn on the vehicle engine\n\n");
		engine_state=1; Sensors_set_menu();
		break;
	case 'b':
		printf("\nTurn off the vehicle engine\n\n");
		engine_state=0; choose_system_state();
		break;
	case 'c':
		printf("\nQuit the system\n");
		break;
	}
}

//options to set sensors
void Sensors_set_menu(){
	printf("Sensors set menu:\n");
	printf("a. Turn off the engine\n");
	printf("b. Set the traffic light color\n");
	printf("c. Set the room temperature\n");
#if (WITH_ENGINE_TEMP_CONTROLLER)
	printf("d. Set the engine temperature\n");
#endif
	char input;

//do while loop to prevent wrong input
	do
	{
#if (WITH_ENGINE_TEMP_CONTROLLER)
		printf("please enter a,b,c or d: ");
#else
		printf("please enter a,b or c: ");
#endif
		scanf(" %c",&input);
		input=tolower(input);
	}
#if (WITH_ENGINE_TEMP_CONTROLLER)
	while (input!='a'&&input!='b'&&input!='c'&&input!='d');
#else
	while (input!='a'&&input!='b'&&input!='c');
#endif

	switch(input)
	{
	case 'a':
		engine_state=0;choose_system_state();
		break;
	case 'b':
		traffic_light_color();
		break;
	case 'c':
		room_temperature();
		break;
#if (WITH_ENGINE_TEMP_CONTROLLER)
	case 'd':
		engine_temperature();
		break;
#endif
	}
			if(vehicle_speed==30)
			{
				AC=1;
				Troom=Troom*5/4+1;
#if (WITH_ENGINE_TEMP_CONTROLLER)
				ETC=1;
				Tengine=Tengine*5/4+1;
#endif
			}
	if(engine_state)
	{
	    display_state();
	    Sensors_set_menu();

	}
}

//determine speed of the vehicle based on traffic light color
void traffic_light_color(){
	printf("enter traffic light color\n");
	char input;
	do
	{
		printf("enter G,O or R: ");
		scanf(" %c",&input);
		input=tolower(input);
	} while (input!='g'&&input!='o'&&input!='r');
	switch(input)
	{
	case 'g':
		vehicle_speed=100;
		break;
	case 'o':
		vehicle_speed=30;
		break;
	case 'r':
		vehicle_speed=0;
		break;
	}
}


//determine room temperature and AC state
void room_temperature(){
	printf("enter room temperature: ");
	scanf("%f",&Troom);
	if((Troom<10)||(Troom>30))
	{
		Troom=20;AC=1;
	}
	else AC=0;
}

//determine engine temperature and Engine Temperature Controller state
#if (WITH_ENGINE_TEMP_CONTROLLER)
void engine_temperature(){
	printf("enter engine temperature: ");
	scanf("%f",&Tengine);
	if((Tengine<100)||(Tengine>150))
	{
		Tengine=125;ETC=1;
	}
	else ETC=0;
}
#endif

//Display the current vehicle state
void display_state(){
	printf("\n\n");
	engine_state?printf("i.   Engine state: ON\n"):printf("i.   Engine state: OFF\n");
	AC?printf("ii.  AC: ON\n"):printf("ii.  AC: OFF\n");
	printf("iii. Vehicle Speed: %d km/hr\n",vehicle_speed);
	printf("iv.  Room Temperature: %.4f C\n",Troom);
#if (WITH_ENGINE_TEMP_CONTROLLER)
	ETC?printf("v.   Engine Temperature Controller State: ON\n"):printf("v.   Engine Temperature Controller State: OFF\n");
	printf("vi.  Engine Temperature: %.4f C\n",Tengine);
#endif
	printf("\n");
}


int main()
{
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	printf("Welcome!!\n");
	choose_system_state();

	return 0;
}
