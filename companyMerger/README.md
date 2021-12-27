**Function:** Keeps track of different companies (represented by integers), allowing the user to merge companies (creating a new, mega company) and split companies (returning all the companies in this mega company to their state right before the previous merge)

**Syntax:** <br />
{ {1}, { {2}, {3} } }
    -> We have a mega company with two subcompanies; the first subcompany is just company 1, while the second subcompany is made up of two more subcompanies, one consisting of just company 2 and the other consisting of just company 3

**Example Walkthrough:** <br />
Starting state: {0}, {1}, {2}, {3}, {4}
merge(0,1) -> { {0}, {1} }, {2}, {3}, {4}
merge(2,3) -> { {0}, {1} }, { {2}, {3} }, {4}
merge(0,3) -> { { {0}, {1} }, { {2}, {3} } }, {4}
split(2) -> { {0}, {1} }, { {2}, {3} }, {4}
split(2) -> { {0}, {1} }, {2}, {3}, {4}
merge(2,4) -> { {0}, {1} }, { {2}, {4} }, {3}
split(0) -> {0}, {1}, { {2}, {4} }, {3}
