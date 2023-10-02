from django.urls import path
from . import views
app_name='mdproject'
urlpatterns = [
    path('', views.index, name='index'),
    path('save/', views.save, name='save'),
    path('crypt/', views.crypt, name='crypt'),
    path('descrypt/', views.descrypt, name='descrypt'),
]
