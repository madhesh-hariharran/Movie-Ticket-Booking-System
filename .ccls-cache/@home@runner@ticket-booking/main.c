#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_TICKETS 100
#define MAX_LENGTH 100

typedef struct {
  char name[MAX_LENGTH];
  char phoneNumber[MAX_LENGTH];
  char age[MAX_LENGTH];
  char city[MAX_LENGTH];
  char theatre[MAX_LENGTH];
  char movie[MAX_LENGTH];
  char time[MAX_LENGTH];
  char date[MAX_LENGTH];
  int ticketCount;
  float totalPrice;
} Ticket;

char *cities[10] = {"Chennai", "Mumbai", "Delhi",   "Bangalore",  "Hyderabad",
                    "Kochi",   "Pune",   "Kolkata", "Chandigarh", "Ahmedabad"};

char *theatres[10][9] = {
    {"AGS Cinemas:Navlur", "Luxe Cinemas: Phoenix Marketcity",
     "Cinepolis:BSR Mall", "Inox:Marina Mall", "PVR:Koyambedu",
     "Sathyam Cinemas: Poonamalle", "Palazzo: Forum Mall",
     "Escape Cinemas: Express Avenue", "Mayajaal Multiplex: ECR"},
    {"Bharath Cineplex: Kurla", "Carnival: Wadala", "Gold Cinema: Dadar",
     "INOX: Rcity", "Regal Cinema: Colaba", "Cinepolis: Seawood Mall",
     "PVR Icon: Andheri", "INOX: Korum Mall", "Fun Cinemas: K Star Mall"},
    {"Full Cinemas: Manhattan", "INOX: MSX Mall", "PVR: Gaur City",
     "Cinepolis: V3S Mall", "Wave: Noida", "Rajhans Cinemas: Noida",
     "US Cinemas: Noida", "Wave Cinemas: Gaur Central Mall",
     "RR Cinemas: Jaipuria Mall"},
    {"Cinepolis: Royal Meenakshi Mall", "INOX: Nexus, White Field",
     "PVR: Vega City", "Santosh Theatre: Gandhi Nagar",
     "Alankar Theatre: Hoskote", "Fun Cinemas: Sigma Mall",
     "Gopalan Cinemas: Arcade Mall", "PVR: Orion Mall",
     "V Cinemas: Sanjaynagar"},
    {"AMB Cinemas: Gachibowli", "INOX: GSM Mall", "Megha Theatre: Dilsukhnagar",
     "PVR: Inorbit Mall", "PVR: RK Cineplex", "Asian Cineplanet: Kompally",
     "Cinepolis: CCPL Mall", "Miraj Cinemas: Shalini Shivani",
     "Moviemax: Secunderabad"},
    {"Carnival Cinemas: RedCarpet", "PVR: Lulu (Gold)", "Shenoys: Kochi",
     "Padma Cinema", "Cinepolis: Centre Square Mall", "G Cinemas: Kochi",
     "Aashirvad Cineplex: Perumbavoor", "Casino Talkies: Aluva",
     "Central Talkies: Thrippunithura"},
    {"Ashok Theatre: Pimpri", "Bollywood Multiplex: Kharadi",
     "Cinepolis: Seasons Mall", "City Pride: R Deccan",
     "Platinum Cinema: Junnar", "Abruhi: Singhagad Road",
     "Inox: Royal Heritage Mall", "PVR: The Pavillion",
     "PVR: Phenix Marketcity"},
    {"INOX: Hiland Park", "Star Theatre: Kolkata", "Cinepolis: Lake Mall",
     "Asoka Cinema: Behala", "Carnival: Salt Lake", "Bioscope: Axis Mall",
     "Carnival: Salt Lake", "PVR: Diamond Plaza", "RDB Cinemas: Salt Lake"},
    {"Cinepolis: Bestech Mall", "PVR: VR Punjab Mall", "Rajhans: Panchkula",
     "Inox: Dillion Plaza", "Fun Cinemas: Fun Republic Mall",
     "Picadily Square: Chandigarh"},
    {"Newfangled Miniplex: Mondeal Retail Park", "19 Cinemas: Narol",
     "AB Miniplex: Shivaranjini Cross Road", "Apple Multiplex: Maninagar",
     "Cinemax: Dev Arc", "Cinepolis: Nexus", "City Gold: Ashram Road",
     "Connplex Smart Theatre: Prahladnagar", "Devi Multiplex: Naroda"}};

char *movies[10] = {"Avatar: The Way of Water",
                    "Ponniyin Selvan",
                    "Black Panther: Wakanda Forever",
                    "KGF: Chapter 2",
                    "Vikram",
                    "RRR",
                    "Major",
                    "Brahmastra: Part One-Shiva",
                    "Oppenheimer",
                    "Thor: Love and Thunder"};

char *times[4] = {"9:00 AM", "2:00 PM", "6:00 PM", "11:00 PM"};

void viewTicket() {
  char phoneNumber[MAX_LENGTH];
  FILE *file = fopen("tickets.txt", "r");
  if (file == NULL) {
    printf("No tickets available.\n");
    return;
  }

  printf("Enter your phone number to view your ticket: ");
  scanf("%s", phoneNumber);

  Ticket ticket;
  int found = 0;
  while (fread(&ticket, sizeof(Ticket), 1, file)) {
    if (strcmp(ticket.phoneNumber, phoneNumber) == 0) {
      printf("\n--- Ticket Details ---\n");
      printf("Name: %s\n", ticket.name);
      printf("Phone Number: %s\n", ticket.phoneNumber);
      printf("Age: %s\n", ticket.age);
      printf("City: %s\n", ticket.city);
      printf("Theatre: %s\n", ticket.theatre);
      printf("Movie: %s\n", ticket.movie);
      printf("Time: %s\n", ticket.time);
      printf("Date: %s\n", ticket.date);
      printf("Number of Tickets: %d\n", ticket.ticketCount);
      printf("Total Price: %.2f\n", ticket.totalPrice);
      found = 1;
      break;
    }
  }
  fclose(file);

  if (!found) {
    printf("No ticket found for phone number %s.\n", phoneNumber);
  }
}

void bookTicket() {
  Ticket newTicket;
  FILE *file = fopen("tickets.txt", "a+");
  if (file == NULL) {
    printf("Error opening file!\n");
    return;
  }

  printf("\nEnter your name: ");
  scanf("%s", newTicket.name);
  printf("Enter your phone number: ");
  scanf("%s", newTicket.phoneNumber);
  printf("Enter your age: ");
  scanf("%s", newTicket.age);

  printf("\nChoose city: \n");
  for (int i = 0; i < 10; i++) {
    printf("%d) %s\n", i + 1, cities[i]);
  }
  int cityChoice;
  printf("Enter city choice [1 to 10]: ");
  scanf("%d", &cityChoice);

  if (cityChoice < 1 || cityChoice > 10) {
    printf("Invalid city choice.\n");
    fclose(file);
    return;
  }
  strcpy(newTicket.city, cities[cityChoice - 1]);

  printf("\nChoose theatre: \n");
  for (int i = 0; i < 9; i++) {
    printf("%d) %s\n", i + 1, theatres[cityChoice - 1][i]);
  }
  int theatreChoice;
  printf("Enter theatre choice [1 to 9]: ");
  scanf("%d", &theatreChoice);

  if (theatreChoice < 1 || theatreChoice > 9) {
    printf("Invalid theatre choice.\n");
    fclose(file);
    return;
  }
  strcpy(newTicket.theatre, theatres[cityChoice - 1][theatreChoice - 1]);

  printf("\nChoose movie: \n");
  for (int i = 0; i < 10; i++) {
    printf("%d) %s\n", i + 1, movies[i]);
  }
  int movieChoice;
  printf("Enter movie choice [1 to 10]: ");
  scanf("%d", &movieChoice);

  if (movieChoice < 1 || movieChoice > 10) {
    printf("Invalid movie choice.\n");
    fclose(file);
    return;
  }
  strcpy(newTicket.movie, movies[movieChoice - 1]);

  printf("\nChoose time: \n");
  for (int i = 0; i < 4; i++) {
    printf("%d) %s\n", i + 1, times[i]);
  }
  int timeChoice;
  printf("Enter time choice [1 to 4]: ");
  scanf("%d", &timeChoice);

  if (timeChoice < 1 || timeChoice > 4) {
    printf("Invalid time choice.\n");
    fclose(file);
    return;
  }
  strcpy(newTicket.time, times[timeChoice - 1]);

  printf("Enter the date for the movie (YYYY-MM-DD): ");
  scanf("%s", newTicket.date);

  printf("Enter the number of tickets: ");
  scanf("%d", &newTicket.ticketCount);

  newTicket.totalPrice =
      newTicket.ticketCount * 250; // Assuming price per ticket is 250

  printf("\n--- Booking Summary ---\n");
  printf("Name: %s\n", newTicket.name);
  printf("Phone Number: %s\n", newTicket.phoneNumber);
  printf("Age: %s\n", newTicket.age);
  printf("City: %s\n", newTicket.city);
  printf("Theatre: %s\n", newTicket.theatre);
  printf("Movie: %s\n", newTicket.movie);
  printf("Time: %s\n", newTicket.time);
  printf("Date: %s\n", newTicket.date);
  printf("Number of Tickets: %d\n", newTicket.ticketCount);
  printf("Total Price: %.2f\n", newTicket.totalPrice);

  char confirm;
  printf("Confirm booking? (y/n): ");
  scanf(" %c", &confirm);

  if (confirm == 'y' || confirm == 'Y') {
    char paymentMethod[MAX_LENGTH];
    printf("\nChoose payment method: \n");
    printf("1) UPI\n");
    printf("2) Netbanking\n");
    printf("3) Debit Card\n");
    printf("4) Credit Card\n");
    int paymentChoice;
    printf("Enter payment choice [1 to 4]: ");
    scanf("%d", &paymentChoice);

    switch (paymentChoice) {
    case 1:
      strcpy(paymentMethod, "UPI");
      break;
    case 2:
      strcpy(paymentMethod, "Netbanking");
      break;
    case 3:
      strcpy(paymentMethod, "Debit Card");
      break;
    case 4:
      strcpy(paymentMethod, "Credit Card");
      break;
    default:
      printf("Invalid payment method.\n");
      fclose(file);
      return;
    }

    printf("Redirecting to %s payment site...\n", paymentMethod);
    sleep(2); // Simulate payment processing time
    printf("Payment successful! Ticket booked.\n");

    fwrite(&newTicket, sizeof(Ticket), 1, file);
  } else {
    printf("Booking cancelled.\n");
  }
  fclose(file);
}

int main() {
  int choice;
  while (1) {
    printf("\n--- Movie Ticket Booking System ---\n");
    printf("1) Book Ticket\n");
    printf("2) View Ticket\n");
    printf("3) Exit\n");
    printf("Enter your choice [1 to 3]: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
      bookTicket();
      break;
    case 2:
      viewTicket();
      break;
    case 3:
      printf("Exiting...\n");
      exit(0);
    default:
      printf("Invalid choice. Please try again.\n");
    }
  }
  return 0;
}
