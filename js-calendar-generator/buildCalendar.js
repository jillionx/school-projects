function drawCalendar(){
var display = document.getElementById("calendar");			//sets area on page to display calendar after running script
var table = '';												//will contain entire markup to display calendar
var maxRows = 5;											//max number of weeks after initial week (6-1)
var maxCols = 7;											//days of the week (0-6)
var month = document.getElementById('month').value;			//pulls user input for month
var year = document.getElementById('year').value;			//pulls user input for year
var maxDays = 0;											//will be set based on month
var m = 1;													//this will be set based off of user input
var y = year;												//this will be the year we calculate the forumla from to account for Jan/Feb


/* verify values entered are at least integers*/
if (isNaN(month) || isNaN(year)) {
	table += 'Input invalid. Please enter in MM and DDDD format';
	display.innerHTML = table;
	return;
}
else if (month < 01 || month > 12) {
	table += 'Month invalid, please select a valid month (01-12)';
	display.innerHTML = table;
	return;
}

/*initiate some stuff! using the month selected: set m values for formula, set maxDays for month selected, text for month to display, change y value for Jan/Feb cases*/
if (month == 01) {
	monthText = 'January';
	m = 13;
	y -= 1;
	maxDays = 31;
}
else if (month == 02) {
	monthText = 'February';
	m = 14;
	y -= 1;
	maxDays = 28;
	/*calculate leap years if February selected*/
	if((year % 4) == 0) {
		if(((year % 100) == 0) && ((year % 400) == 0)) {
			maxDays = 29;
		}
		else if(((year % 100) == 0) && ((year % 400) != 0)) {
			maxDays = 28;
		}
		else {
			maxDays = 29;
		}
	}
}
else if (month == 03){
	monthText = 'March';
	m = 3;
	maxDays = 31;
}
else if (month == 04){
	monthText = 'April';
	m = 4;
	maxDays = 30;
}
else if (month == 05){
	monthText = 'May';
	m = 5;
	maxDays = 31;
}
else if (month == 06){
	monthText = 'June';
	m = 6;
	maxDays = 30;
}
else if (month == 07){
	monthText = 'July';
	m = 7;
	maxDays = 31;
}
else if (month == 08){
	monthText = 'August';
	m = 8;
	maxDays = 31;
}
else if (month == 09){
	monthText = 'September';
	m = 9;
	maxDays = 30;
}
else if (month == 10){
	monthText = 'October';
	m = 10;
	maxDays = 31;
}
else if (month == 11){
	monthText = 'November';
	m = 11;
	maxDays = 30;
}
else if (month == 12){
	monthText = 'December';
	m = 12;
	maxDays = 31;
}
else {
	table += 'Month Invalid, please select a valid date format';
	display.innerHTML = table;
}

/* set and calculate remaining variables and then calculate the h value */
var q = 1;								//calculating start day, so this is 1
var K = y % 100;						//calculates year of the century
var j = Math.floor(y/100);				//calculates zero-based century
var day = 1;							//day of the month we'd like to calculate

var h = ((q + (Math.floor((13 * ((m + 1) / 5)))) + K + (Math.floor(K / 4)) + (Math.floor(j / 4)) - (2 * j)) % 7);

/*convert Saturday h value to "end of week" for easy looping*/
if (h == 0) {
	h = 7;
}

/*create the headers - month/year/days of week*/
table += '<tr><th colspan=7>' +
	monthText + ' ' + year + '</th></tr><tr>' +
	'<th>Sunday</th><th>Monday</th><th>Tuesday</th><th>Wednesday</th>' + 
	'<th>Thursday</th><th>Friday</th><th>Saturday</th></tr>';

/*for row 1 - find starting day, fill with blanks beforehand*/
var drawRow = '<tr>'
for(col = 1; col <= maxCols; col++) {
	if (col < h) {
		drawRow += '<td class="blankday">&nbsp;</td>';
	}
	if (col >= h) {
		for (col; col <= maxCols; col++) {
		drawRow += '<td>' + day + '</td>';
		day = day + 1;
		}
	}
}
table += drawRow + '</tr>';

/*complete the calendar! */
for(var row = 1; row <= (maxRows); row++) {
	var drawRow = '<tr>'
	for(col = 1; col <= maxCols; col++) {
		if (day > maxDays) {
			break;
		}
		drawRow += '<td>' + day + '</td>';
		day = day + 1;
	}
	if (col <= maxCols) {
		for (col; col <= maxCols; col++) {
		drawRow += '<td class="blankday">&nbsp;</td>';
		}
	}
	table += drawRow + '</tr>';
	/*break the calendar if we've reached maxDays by the end of a row*/
	if (day > maxDays) {
		break;
	}
}
/*display results of table!*/
display.innerHTML = table;
}