import yaml

with open('hw4fortunes.yml', 'r', encoding='utf-8') as file:
    fortunes = yaml.safe_load(file)

with open('fortunes.ldif', 'w', encoding='utf-8') as ldif_file:
    for fortune in fortunes:
        dn = f"cn=fortune-{fortune['ID']},ou=Fortune,dc=35,dc=nasa"
        ldif_file.write(f"dn: {dn}\n")
        ldif_file.write("objectClass: top\n")
        ldif_file.write("objectClass: fortune\n")
        ldif_file.write(f"cn: fortune-{fortune['ID']}\n")
        ldif_file.write(f"author: {fortune['Author']}\n")
        ldif_file.write(f"id: {fortune['ID']}\n")
        ldif_file.write(f"description: {fortune['Description']}\n\n")
