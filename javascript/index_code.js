
var SelectedRows = [];

function isValueUnique(jsonData, valueToCheck) {
    for (i = 0; i < jsonData.length; i++){
          if(JSON.stringify(jsonData[i]) == JSON.stringify(valueToCheck))
              return false;
    }
    return true;
}

function handleRowClick(event) {
      // Check if the clicked element is a table row (not a header or button)
      const row = event.target.closest("tr");
      if (row && row.parentNode.tagName === "TBODY") {
        // Get the row's data (for example, all cell content)
        const rowData = [];
        const cells = row.querySelectorAll("td");

        cells.forEach(cell => {
          rowData.push(cell.textContent.trim());
        });

      let savedData = JSON.parse(localStorage.getItem("selectedRowData")) || [];

      // Append the new row's data to the saved data array
      if(isValueUnique(SelectedRows, rowData)){
        SelectedRows.push(rowData);
      }
      //console.log(JSON.stringify(savedData));


      // Store the updated array back into localStorage
      localStorage.setItem("selectedRowData", JSON.stringify(SelectedRows));
      }
}

function addTableClickListener() {
      const table = document.querySelector("#userTable");

      // Attach a click event listener to the table
      table.addEventListener("click", handleRowClick);
}

    // Wait until the DOM is fully loaded before adding the event listener
document.addEventListener("DOMContentLoaded", addTableClickListener);

function clearinput(input){
    input.value = ''; // Clears the input field
}

// window.onload = function() {
//     SelectedRows = [];
//     localStorage.removeItem("selectedRowData");
//     localStorage.removeItem("SelectedRows");
// }

function search() {
    var input1, input2, input3, input4, filter1, filter2, filter3, filter4, table, tr, td, i, txtValue, rowText;
    input1 = document.getElementById("myInput1");
    input2 = document.getElementById("myInput2");
    input3 = document.getElementById("myInput3");
    input4 = document.getElementById("myInput4");
    filter1 = input1.value.toUpperCase();
    filter2 = input2.value.toUpperCase();
    filter3 = input3.value.toUpperCase();
    filter4 = input4.value.toUpperCase();

    table = document.getElementById("userTable");
    tr = table.querySelectorAll("tbody tr");

    // Loop through all table rows, and hide those who don't match the search query
    for (i = 0; i < tr.length; i++) {
        td = tr[i].getElementsByTagName("td");
        rowText = ''; // Initialize an empty string to hold text for this row

        // Loop through each cell in the row
        for (var j = 0; j < td.length; j++) {
            if (td[j]) {
                rowText += td[j].textContent || td[j].innerText; // Append text of each cell to rowText
            }
        }

         // If any cell in the row contains the search query, display the row, otherwise hide it
    if (rowText.toUpperCase().indexOf(filter1) > -1 && rowText.toUpperCase().indexOf(filter2) > -1 && rowText.toUpperCase().indexOf(filter3) > -1 && rowText.toUpperCase().indexOf(filter4) > -1) {
        tr[i].style.display = "";

         // find cells that contain filter text
        for (let rowcell = 0; rowcell < tr[i].cells.length; rowcell++) {
            let cell = tr[i].cells[rowcell]; // Get the cell
            let cellText = " " + cell.textContent || cell.innerText; // Get text inside cell - and prepend space - hacky solution for string searching
            console.log("tekst u cellu je",cellText);
            if((cellText.toUpperCase().indexOf(filter1) > 0) ||
               (cellText.toUpperCase().indexOf(filter2) > 0) ||
               (cellText.toUpperCase().indexOf(filter3) > 0) ||
               (cellText.toUpperCase().indexOf(filter4) > 0)){
                    cell.style.backgroundColor = "lightgreen"; // Highlight matching cell
                    cell.style.color = "black"; // Change text color for better visibility
            }
            else{
                cell.style.backgroundColor = ""; // This removes the inline style
            }
        }
    } else {
        tr[i].style.display = "none";
    }
    }
}

function clearentries() {
    document.getElementById("myInput1").value ='';
    document.getElementById("myInput2").value ='';
    document.getElementById("myInput3").value ='';
    document.getElementById("myInput4").value ='';
    table = document.getElementById("userTable");
    tr = table.querySelectorAll("tbody tr");

    for (i = 0; i < tr.length; i++) { // loop through table rows
        td = tr[i].getElementsByTagName("td");

        tr[i].style.display = "";
        // Loop through each cell in the row
        for (var j = 0; j < td.length; j++) {
            if (td[j]) {
              td[j].style.backgroundColor = "white"; // This removes the inline style
              td[j].style.backgroundColor = ""; // This removes the inline style
              console.log("cell: ", td[j].textContent);
            }
        }
     }
}

function animateScrollTo(element, targetPosition, duration) {
    const startPosition = element.scrollTop;
    const distance = targetPosition - startPosition;
    let startTime = null;

    function scrollStep(currentTime) {
        if (!startTime) startTime = currentTime;
        const timeElapsed = currentTime - startTime;
        const progress = Math.min(timeElapsed / duration, 1); // Normalize to range [0, 1]
        const currentScroll = startPosition + distance * progress;
        element.scrollTop = currentScroll;

        if (progress < 1) {
            requestAnimationFrame(scrollStep); // Continue animation
        }
    }

    // Start the animation
    requestAnimationFrame(scrollStep);
}

document.getElementById("generator").addEventListener("click", function() {
    const targetPosition = document.getElementById("myInput1").offsetTop;
    // Animate scroll to the target position (using document.documentElement or document.body)
    animateScrollTo(document.documentElement, targetPosition - 20, 250);
});

function GenerateArmy(){
    //clearOutput();
    let Race = document.getElementById("races").value;
    let ArmySize = document.getElementById("regsize").value;
    let RaceChoice = -1;
    switch(Race){
        case "empire":
            RaceChoice = 1;
            break;
        case "elves":
            RaceChoice = 2;
            break;
        case "dwarves":
            RaceChoice = 3;
            break;
        case "woodelves":
            RaceChoice = 4;
            break;
        case "chaos": RaceChoice = 5;
            break;
        case "orcs": RaceChoice = 6;
            break;
        case "vc": RaceChoice = 7;
            break;
        case "skaven": RaceChoice = 8;
            break;
        default:
             throw "invalid race";
     }
     let stringPointer = _PrintToJson(ArmySize, RaceChoice);

     // Get the length of the string (you might need to know this, or you can calculate it)
     let stringLength = 0;
          while(HEAPU8[stringPointer + stringLength] !== 0){
              stringLength++;
      }

     // Read the string from WebAssembly memory
     const str = UTF8ToString(stringPointer, stringLength);
     JSON.stringify(str);
     if(str === "[\n]"){ // check if nothing is returned;
         console.log("empty json");
         return;
    }
     let obj = JSON.parse(str);
     createTableFromJSON(obj);
}

function createTableFromJSON(jsonData) {
      const table = document.querySelector("#userTable");
      const tableHead = table.querySelector("thead");
      const tableBody = table.querySelector("tbody");

      // Clear existing table content
      tableHead.innerHTML = "";
      tableBody.innerHTML = "";


      const headers = [...new Set(jsonData.flatMap(obj => Object.keys(obj)))];

      const headerRow = document.createElement("tr");

      // Loop through the keys and create table headers
      headers.forEach(header => {
        const th = document.createElement("th");
        th.textContent = header.replace(/_/g, " ").toUpperCase();  // Optional: format header text
        headerRow.appendChild(th);
      });

      // Append headers to the table
      tableHead.appendChild(headerRow);

      // Create rows for each object in the JSON data
      jsonData.forEach(item => {
        const row = document.createElement("tr");

        // Loop through each header and create a cell for each key
        headers.forEach(header => {
          const cell = document.createElement("td");
          // Insert value or an empty string if key is missing in this object
          cell.textContent = item[header] || '';
          row.appendChild(cell);
        });

        // Append the row to the table body
        tableBody.appendChild(row);
      });
}




      var Module = {
        preRun: [],
        postRun: [],
        print: (function() {
          var element = document.getElementById('output');
          if (element) element.value = ''; // clear browser cache
          return function(text) {
            if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
            // These replacements are necessary if you render to raw HTML
            //text = text.replace(/&/g, "&amp;");
            //text = text.replace(/</g, "&lt;");
            //text = text.replace(/>/g, "&gt;");
            //text = text.replace('\n', '<br>', 'g');
            console.log(text);
            if (element) {
              element.value += text + "\n";
              element.scrollTop = element.scrollHeight; // focus on bottom
      }
          };
        })(),
        setStatus: function(text) {
          if (!Module.setStatus.last) Module.setStatus.last = { time: Date.now(), text: '' };
          if (text === Module.setStatus.last.text) return;
          var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
          var now = Date.now();
          if (m && now - Module.setStatus.last.time < 30) return; // if this is a progress update, skip it if too soon
          Module.setStatus.last.time = now;
          Module.setStatus.last.text = text;
        },
        totalDependencies: 0,
        monitorRunDependencies: function(left) {
          this.totalDependencies = Math.max(this.totalDependencies, left);
          Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies-left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
        }
      };
      Module.setStatus('Downloading...');
      window.onerror = function(event) {
        // TODO: do not warn on ok events like simulating an infinite loop or exitStatus
        Module.setStatus('Exception thrown, see JavaScript console');
        Module.setStatus = function(text) {
          if (text) Module.printErr('[post-exception status] ' + text);
        };
      };