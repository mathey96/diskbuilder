   // finds largest subarray in json
   function find_table_size(table){
       let largestSubarray = table[0];

       table.forEach(subarray => {
           if (subarray.length > largestSubarray.length) {
               largestSubarray = subarray; // Update if we find a larger array
           }
       });
       return largestSubarray.length;
   }

    function clear_table(){
        const table = document.getElementById("table");
        const tableHead = table.querySelector("thead");
        const tableBody = table.querySelector("tbody");
        tableHead.innerHTML = "";
        tableBody.innerHTML = "";
        localStorage.removeItem("selectedRowData");
        var SelectedRows = JSON.parse(localStorage.getItem('SelectedRows'));
        SelectedRows = null;
        window.location.href = 'index.html'; // Path to your HTML page
   }

window.SelectedRows = null;
window.onload = function() {

    document.getElementById('cleartable').style.visibility = 'show';
    // Retrieve the stored row data from localStorage
    const JSONArray = JSON.parse(localStorage.getItem("selectedRowData"));

    if (JSONArray) {
        // Create a new table dynamically
        const table = document.createElement("table");
        table.id = "table"; // Add the ID here
        table.border = "1";

        // Create the thead element
        const tableHead = document.createElement("thead");

        // Create table headers
        let table_size = find_table_size(JSONArray);

        const headerRow = document.createElement("tr");
        let headers = [];
        for (i = 0; i < table_size; i++) {
            if (i == 0) {
                headers.push("sum");
            } else {
                let disk_no = "disk " + i;
                headers.push(disk_no);
            }
        }

        headers.forEach(header => { // creating headers
            const th = document.createElement("th");
            th.textContent = header;
            headerRow.appendChild(th);
        });

        tableHead.appendChild(headerRow);

        table.appendChild(tableHead);

        const tableBody = document.createElement("tbody");

        JSONArray.forEach(item => {
            const row = document.createElement("tr");
            item.forEach(CellIndex => {
                const cell = document.createElement("td");
                cell.textContent = CellIndex;
                row.appendChild(cell);
            });
            tableBody.appendChild(row);
        });

        table.appendChild(tableBody);

        document.body.appendChild(table);
    } else {
        const newPara = document.createElement('p');
        newPara.textContent = 'No data found! Go Back and click on the rows of possible armies to save them to the draft ';
        document.body.appendChild(newPara);
        document.getElementById('cleartable').style.visibility = 'hidden';
    }
}