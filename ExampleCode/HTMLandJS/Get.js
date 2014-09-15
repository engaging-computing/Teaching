
URL = 'http://rsense-dev.cs.uml.edu/api/v1/projects/683';
response = $.ajax({ type: "GET",
				url: URL,
				async: false,
				dataType: "JSON"
				}).responseText;
arg = JSON.parse(response);

console.log(arg); //prints to console entire response that is JSON parsed

console.log(arg.id);
