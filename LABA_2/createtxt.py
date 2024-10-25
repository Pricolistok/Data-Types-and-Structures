from random import randint, uniform


def main():
    rc = int(input('Введите выбор 1 - файл для сортировки 2 - файл - радомный: '))
    arr_composers = ['Ivanox', 'Sidorov', 'Dokolin', 'Kozlov', 'Sadekov', 'Epifanovskiy', 'Pirogov']
    arr_countries = ['Russia', 'Gvatemala', 'Germany', 'USA', 'China', 'Kazacstan', 'Belsrus', 'Kuba']
    arr_theaters = ['The Big Theater', 'Moscow Art Theater', 'Vakhtangov Theater', 'Mriinsky theater']
    arr_shows = ['Nutcker', 'Mask', 'Anna Karenina', 'Kolobok', 'Gore ot Uma', 'Oblomoff', 'Revizor']
    if rc == 1:
        file_name = './data/for_sort'
        size = 1000
    else:
        file_name = './data/random_file'
        size = randint(10, 100)
    with open(file_name, 'w') as file:
        for i in range(size):
            file.write(arr_theaters[randint(0, 3)] + '\n')
            file.write(arr_shows[randint(0, 6)] + '\n')
            start_price = round(uniform(100, 1000), 2)
            finish_price = round(uniform(start_price, start_price + 10000), 2)
            file.write(f'{start_price}\n')
            file.write(f'{finish_price}\n')
            if rc == 1:
                type_of_show = 5
            else:
                type_of_show = randint(1, 5)

            if i != size - 1:
                add = '\n'
            else:
                add = ''

            if type_of_show == 5:
                file.write(f'5\n')
                file.write(arr_composers[randint(0, 6)] + '\n')
                file.write(arr_countries[randint(0, 6)] + '\n')
                file.write(f'{randint(1, 3)}\n')
                file.write(f'{randint(1, 3)}\n')
                file.write(f'{randint(110, 200)}' + add)

            elif type_of_show == 4:
                file.write(f'4\n')
                file.write(f'{randint(1, 3)}' + add)

            else:
                file.write(str(type_of_show) + add)


if __name__ == '__main__':
    main()