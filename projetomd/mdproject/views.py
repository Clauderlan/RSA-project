from django.shortcuts import render
from django.http import JsonResponse, HttpResponse
import ctypes

# Create your views here.
def index(request):
    return render(request, 'mdproject/index.html', {})

def result(request):
     # Carregue a biblioteca compartilhada
    random_lib = ctypes.CDLL('./mdproject/c_code/crypt.dll')

        # Chame a função C para gerar um número aleatório
    random_number = random_lib.generate_random()
    print(random_number)
    return render(request, 'mdproject/result.html', {})



def save(request):
    try:
        if request.method == 'POST':
            primo1 = request.POST.get('primo1', '')
            primo2 = request.POST.get('primo2', '')
            e = request.POST.get('e', '')

            if primo1 and primo2 and e:  # Verifique se todos os campos foram preenchidos
                random_lib = ctypes.CDLL('C:/Users/Usúario/projetomd/mdproject/c_code/menu.dll')  # Substitua pelo caminho correto para sua biblioteca

                primo1 = int(primo1)
                primo2 = int(primo2)
                e = int(e)
                
                #string = ctypes.c_char_p(b"Text")
                #pyGenKey = random_lib.gerarChavePub#(primo1, primo2, e)
                #pyGenKey.argtypes = [ctypes.c_longlong, ctypes.c_longlong, ctypes.c_longlong]
                #pyGenKey.restype = ctypes.c_int 
                # Chame a função C para gerar as chaves públicas e verifique o status
                status_code = random_lib.gerarChavePub(primo1, primo2, e)
                if status_code == 1:
                    status = 'Primo 1 inválido'
                elif status_code == 2:
                    status = 'Primo 2 inválido'
                elif status_code == 3:
                    status = 'Expoente inválido'
                else:
                    status = 'Chaves públicas geradas com sucesso'

                return render(request, 'mdproject/save.html', {'status': status})
            else:
                return render(request, 'mdproject/save.html', {'status': 'Preencha todos os campos'})
        else:
            return render(request, 'mdproject/save.html', {'status': ''})
    except Exception as e:
        return JsonResponse({'error': str(e)})



def crypt(request):
    try:
        if request.method == 'POST':
            mensagem = request.POST.get('mensagem', '')
            n = request.POST.get('n', '')
            e = request.POST.get('e', '')
            if n and e:
                random_lib = ctypes.CDLL('C:/Users/Usúario/projetomd/mdproject/c_code/menu.dll')

                n = int(n)
                e = int(e)
                
                status = random_lib.encriptarMenu(mensagem.encode(), n, e)
                #return HttpResponse(status)
                if status == 0:
                    status = 'Mensagem criptografada com sucesso'
                else:
                    status = 'Erro na criptografia'
                return render(request, 'mdproject/crypt.html', {'status': status})
            else:
                return HttpResponse("Texto de entrada vazio.", status=400)
        else:
            return render(request, 'mdproject/crypt.html', {})
    except Exception as e:
        return JsonResponse({'error': str(e)})
    
    
    
def descrypt(request):
    try:
        if request.method == 'POST':
            p = request.POST.get('p', '')
            q = request.POST.get('q', '')
            e = request.POST.get('e', '')
            if p and q and e:
                # Carregue a biblioteca compartilhada
                random_lib = ctypes.CDLL('C:/Users/Usúario/projetomd/mdproject/c_code/menu.dll')  # Substitua pelo caminho correto para sua biblioteca
                
                p = int(p)
                q = int(q)
                e = int(e)
                status = random_lib.desencriptarMenu(p, q, e)
                
                if status == 0:
                    status = 'Mensagem descriptografada com sucesso'
                
                return render(request, 'mdproject/decrypt.html', {'status': status})
            else:
                return HttpResponse("Texto de entrada vazio.", status=400)
        else:
            return render(request, 'mdproject/decrypt.html', {})
    except Exception as e:
        return JsonResponse({'error': str(e)})