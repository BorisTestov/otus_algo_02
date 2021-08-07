#include "tester.h"
#include "stringlengths.h"
#include "luckytickets.h"

// time spent - 100min

int main() {
    auto stringTask = std::make_shared<StringLengths>();
    Tester stringTester(stringTask, "../tests/0.String");
    stringTester.RunTests();
    auto ticketTask = std::make_shared<TicketCounter>();
    Tester ticketTester(ticketTask, "../tests/1.Tickets");
    ticketTester.RunTests(true);
    return 0;
}
