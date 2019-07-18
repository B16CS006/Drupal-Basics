

## How to use
* First Enable the module
* Now check all those option from which you want to use this module in the configuration page of this module
* Now call the api in the following format remember to login before proceed if authentication is enabled

For login use 
```
POST localhost/sampleapi/user/login
```

To get token value
```
GET localhost/services/session/token
```

### GET

To get node
```
GET localhost/sampleapi/node/1

header => {
    "Content-type" = "application/json",
    "X-CSRF-Token" = <Token>
}
```

To get field_collection_item
```
GET localhost/sampleapi/test/field_collection_item/22

header => {
    "Content-type" = "application/json",
    "X-CSRF-Token" = <Token>
}
```

To get taxonomy_term
```
GET localhost/sampleapi/taxonomy_term/22

header => {
    "Content-type" = "application/json",
    "X-CSRF-Token" = <Token>   
}
```

To get Vocabulary
```
GET localhost/sampleapi/taxonomy_vocabulary/city

header => {
    "Content-type" = "application/json",
    "X-CSRF-Token" = <Token>   
}
```

### POST

To create a new node
```
POST localhost/sampleapi/node

header => {
    "Content-type" = "application/json",
    "X-CSRF-Token" = <Token>
}

body => {
  "title": "marvel1",
  "type": "chat_album",
  "body": "description",
  "field_image": [
  	32,
  	{
  		"fid":1,
  		"title":"title"
  	}
  ]
}
```

To create field_collection_item
```
POST localhost/sampleapi/test/field_collection_item

header => {
    "Content-type" = "application/json",
    "X-CSRF-Token" = <Token>
}

body => {
	"field_collection_item": "field_employee_details",
	"field_city":"1",
	"field_first_name": "chetan",
	"field_middle_name": "prakash",
	"field_last_name": "meena",
	"field_mobile_number": "7727931260",
	"field_email": "meena.13@iitj.ac.in",
	"field_age": "12",
	"field_salary": "25000",
	"field_username": "meena.13"
}
```

To create taxonomy_term
```
POST localhost/sampleapi/taxonomy_term

header => {
    "Content-type" = "application/json",
    "X-CSRF-Token" = <Token>   
}

body => {
	"vocabulary_machine_name": "city",
	"name" : "japan"
}
```

To Create Vocabulary
```
POST localhost/sampleapi/taxonomy_vocabulary

header => {
    "Content-type" = "application/json",
    "X-CSRF-Token" = <Token>   
}

body => {
	"name" : "new vocabualry",
	"machine_name" : "new_vocabulary"
}
```