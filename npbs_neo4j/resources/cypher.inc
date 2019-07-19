<?php


file = neo4j.conf
dbms.security.allow_csv_import_from_file_urls=true  => UNCOMMENT IT
dbms.directories.import=import                      => COMMENT IT


/**
 * Loading node with title
 */
LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/node.csv" AS x
MERGE (title:title{
    title: x.title
})
MERGE (node:node{
    nid: toInteger(x.nid),
    vid: toInteger(x.vid),
    type: x.type,
    language: x.language,
    uid: toInteger(x.uid),
    status: toInteger(x.status),
    created: toInteger(x.created),
    changed: toInteger(x.changed),
    comment: toInteger(x.comment),
    promote: toInteger(x.promote),
    sticky: toInteger(x.sticky),
    tnid: toInteger(x.tnid),
    translate: toInteger(x.translate)
})
MERGE (node)-[:TITLE]->(title)
return *


LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_body.csv" AS x
CREATE (body:TextWithSummary{
	value: x.body_value,
    summary: x.body_summary,
    format: x.body_format,
    entity_id: x.entity_id
})

match (b:TextWithSummary)
match (n:ContentType) where n.nid = toInteger(b.entity_id)
merge (n)-[:FIELD_DATA_BODY]->(b)


LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_age.csv" AS x
match (n) where x.entity_type in labels(n) and n.item_id = x.entity_id
merge (age:number_integer{entity_id:x.entity_id, language: x.language, delta:x.delta, value: x.field_age_value})
merge (n)-[:FIELD_AGE]->(age)


LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_asdf.csv" AS x
match (n) where x.entity_type in labels(n) and n.nid = toInteger(x.entity_id)
merge (asdf:email{entity_id:toInteger(x.entity_id), language: x.language, delta:toInteger(x.delta), email: x.field_asdf_email,deleted:toInteger(x.deleted)})
merge (n)-[:FIELD_ASDF]->(asdf)
return n,asdf




LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_city.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (city:taxonomy_term) where toInteger(city.tid) = toInteger(x.field_city_tid)
merge (n)-[:FIELD_CITY]->(city)
return n,city







LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_designation.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    else -1
end = toInteger(x.entity_id)
with n,x
merge (n)-[:FIELD_DESIGNATION]->(designation:list_text{
	language: x.language,
    delta: toInteger(x.delta),
    value: x.field_designation_value
})

RETURN n,designation







LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_domain.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (domain:taxonomy_term_reference) where toInteger(domain.tid) = toInteger(x.field_domain_tid)
merge (n)-[:FIELD_DOMAIN]->(domain)









LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_email.csv" AS x
match (n) where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
merge (email:email{entity_id:toInteger(x.entity_id), language: x.language, delta:toInteger(x.delta), email: x.field_email_email,deleted:toInteger(x.deleted)})
merge (n)-[:FIELD_EMAIL]->(email)
return n,email









LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_employee_details.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (y:field_collection_item) where toInteger(y.item_id) = toInteger(x.field_employee_details_value)
merge (n)-[:FIELD_EMPLOYEE_DETAILS]->(y)











LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_first_name.csv" AS x
match (n) where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)

merge (y:text{entity_id:toInteger(x.entity_id), language: x.language, delta:toInteger(x.delta), value: x.field_first_name_value})
merge (n)-[:FIELD_FIRST_NAME]->(y)
return n,y












LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_geofield.csv" AS x
match (n) where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)

merge (y:geofield{entity_id:toInteger(x.entity_id), language: x.language, delta:toInteger(x.delta),deleted:x.deleted, type:x.field_geofield_geo_type, geom:x.field_geofield_geom, lat:x.field_geofield_lat, lon:x.field_geofield_lon,
left:x.field_geofield_left, top:x.field_geofield_top, right:x.field_geofield_right, bottom:x.field_geofield_bottom,
geohash:x.field_geofield_geohash})

merge (n)-[:FIELD_GEOFIELD]->(y)
return n,y











LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_hero.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    when exists(n.tid) then toInteger(n.tid)
    else -1
end = toInteger(x.entity_id)
with n,x
match (y:node) where toInteger(y.nid) = toInteger(x.field_hero_target_id)
merge (n)-[:FIELD_HERO]->(y)











LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_last_name.csv" AS x
match (n) where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)

merge (y:text{entity_id:toInteger(x.entity_id), language: x.language, delta:toInteger(x.delta), value: x.field_last_name_value})
merge (n)-[:FIELD_LAST_NAME]->(y)
return n,y







LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_link.csv" AS x
match (n) where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)

merge (y:link_field{entity_id:toInteger(x.entity_id), language: x.language, delta:toInteger(x.delta),deleted:x.deleted, url: x.field_link_url, title:x.field_link_title, attributes:x.field_link_attributes})
merge (n)-[:FIELD_LINK]->(y)
return n,y











LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_middle_name.csv" AS x
match (n) where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)

merge (y:text{entity_id:toInteger(x.entity_id), language: x.language, delta:toInteger(x.delta), value: x.field_middle_name_value})
merge (n)-[:FIELD_MIDDLE_NAME]->(y)
return n,y









LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_mobile_number.csv" AS x
match (n) where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)

merge (y:mobile_number{
	entity_id:toInteger(x.entity_id), 
    language: x.language, 
    delta:toInteger(x.delta),
    deleted:x.deleted,
    value: x.field_mobile_number_value,
    country: x.field_mobile_number_country,
    local_number: x.field_mobile_number_local_number,
    verified: x.field_mobile_number_verified,
    tfa: x.field_mobile_number_tfa
})

merge (n)-[:FIELD_MOBILE_NUMBER]->(y)
return n,y









LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_nature.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (y:taxonomy_term) where toInteger(y.tid) = toInteger(x.field_nature_tid)
merge (n)-[:FIELD_NATURE]->(y)
return n,y











LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_ngo_type.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (y:taxonomy_term) where toInteger(y.tid) = toInteger(x.field_ngo_type_tid)
merge (n)-[:FIELD_NGO_TYPE]->(y)
return n,y















LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_salary.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

merge (y:number_integer{entity_id:x.entity_id, language: x.language, delta:x.delta, value: x.field_salary_value})
merge (n)-[:FIELD_SALARY]->(y)
return n,y














LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_skill.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    when exists(n.tid) then toInteger(n.tid)
    else -1
end = toInteger(x.entity_id)
with n,x
match (y:node) where toInteger(y.nid) = toInteger(x.field_skill_target_id)
merge (n)-[:FIELD_SKILL]->(y)
return n,y













LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_state.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (y:taxonomy_term) where toInteger(y.tid) = toInteger(x.field_state_tid)
merge (n)-[:FIELD_STATE]->(y)
return n,y











LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_tags.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (y:taxonomy_term) where toInteger(y.tid) = toInteger(x.field_tags_tid)
merge (n)-[:FIELD_TAGS]->(y)
return n,y










LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_technique.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (y:taxonomy_term) where toInteger(y.tid) = toInteger(x.field_technique_tid)
merge (n)-[:FIELD_TECHNIQUE]->(y)
return n,y










LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_type.csv" AS x
match (n)
where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)
with n,x

match (y:taxonomy_term) where toInteger(y.tid) = toInteger(x.field_type_tid)
merge (n)-[:FIELD_TYPE]->(y)
return n,y
















LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/field_data_field_username.csv" AS x
match (n) where x.entity_type in labels(n) and
case
	when exists(n.nid) then toInteger(n.nid)
    when exists(n.item_id) then toInteger(n.item_id)
    else -1
end = toInteger(x.entity_id)

merge (y:text{entity_id:toInteger(x.entity_id), language: x.language, delta:toInteger(x.delta), value: x.field_username_value})
merge (n)-[:FIELD_USERNAME]->(y)
return n,y












LOAD CSV WITH HEADERS FROM "file:///home/krrishna/Workspace/NPBridge/drupal/node.csv" AS x
MATCH (n:node) where toInteger(n.nid) = toInteger(x.nid) and toInteger(n.vid) = toInteger(x.vid)
set n.type = x.type
return n{.*}