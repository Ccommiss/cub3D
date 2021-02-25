#include "cub3d.h"

void   swap(t_spr *tmp, t_spr *tmp_next)
{
    t_spr val_tmp;

    val_tmp.x = tmp->x;
	val_tmp.y = tmp->y;
	val_tmp.distance = tmp->distance;
	tmp->x = tmp_next->x;
	tmp->y = tmp_next->y;
	tmp->distance = tmp_next->distance;
	tmp_next->x = val_tmp.x;
	tmp_next->y = val_tmp.y;
	tmp_next->distance = val_tmp.distance;
}

t_spr *sort_sprites(t_data *data, t_spr *head)
{
	t_spr *tmp;
	t_spr *tmp_next;
    
	tmp = data->spr;
	tmp_next = data->spr->next;
	while (tmp_next != NULL)
	{
		while (tmp_next != tmp)
		{
			if (tmp_next->distance > tmp->distance)
                swap(tmp, tmp_next);
			tmp = tmp->next;
		}
		tmp = head;
		tmp_next = tmp_next->next;
	}
	return (tmp); 
}


void sprite_casting(t_data *data)
{
	t_spr *head;
	head = data->spr->head; 

	printf("INDEX IN SPR CASTING = %d \n", data->spr->index);
	while (data->spr != NULL)
	{
		data->spr->distance = (pow((data->pos_x - data->spr->x), 2) + pow((data->pos_y - data->spr->y), 2));
		data->spr = data->spr->next;
	}
	data->spr = head;
	data->spr = sort_sprites(data, head);
	data->spr = head;
}



void compute_data(t_data *data, t_spr_geo *sp)
{
   	sp->x = (data->spr->x + 0.5) - data->pos_x; 
	sp->y = (data->spr->y + 0.5) - data->pos_y;

	sp->inv = 1.0 / (data->planeX * data->dirY - data->dirX * data->planeY); //required for correct matrix multiplication
	sp->trans_x = sp->inv * (data->dirY * sp->x - data->dirX * sp->y);
	sp->trans_y = sp->inv * ((-data->planeY * sp->x) + (data->planeX * sp->y)); //this is actually the depth inside the screen, that what Z is in 3D
    sp->screen_x = (int)((data->width / 2) * (1 + sp->trans_x / sp->trans_y));

		// //calculate height of the sprite on screen
	sp->height = abs((int)(data->height / (sp->trans_y)));
    sp->width = abs((int)(data->height / (sp->trans_y)));
}


void sprite_drawing(t_data *data, int x)
{
	t_spr *head = data->spr->head;
    t_spr_geo sp;  

	while (data->spr != NULL)
	{
        compute_data(data, &sp);
		printf(" %d \n", sp.height);
		printf(" %d \n", sp.width);
		printf(" %f \n", sp.x);
		printf(" %f \n", sp.y);
		printf(" %f \n", sp.trans_x);
		printf(" %f \n", sp.trans_y);
		printf(" %d \n", sp.screen_x);
		printf(" %f \n", sp.inv);

		int drawStartY = -sp.height / 2 + data->height / 2;
		if (drawStartY < 0)
			drawStartY = 0;

		int drawEndY = sp.height / 2 + data->height / 2;
		if (drawEndY >= data->height)
			drawEndY = data->height - 1;

		int drawStartX = -sp.width / 2 + sp.screen_x;
		if (drawStartX < 0)
			drawStartX = 0;

		int drawEndX = sp.width / 2 + sp.screen_x;
		if (drawEndX >= data->width)
			drawEndX = data->width - 1;


		for (int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)(256 * (stripe - (-sp.width / 2 + sp.screen_x)) * data->spw / sp.width) / 256;
			unsigned int color;
			if (sp.trans_y > 0 && stripe > 0 && stripe < data->width && sp.trans_y <= data->zbuffer[stripe]) //en enlevant derniere condition ca affiche tout
			{
				for (int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
				{
					int d = (y)*256 - data->height * 128 + sp.height * 128; //256 and 128 factors to avoid floats
					int texY = ((d * data->sph) / sp.height) / 256;
					color = ((unsigned int *)data->sprimgaddr)[data->spw * texY + texX];
					if ((color & 0x00FFFFFF) != 0)
						my_mlx_pixel_put(data, stripe, y, color);
					(void)x;
				}
			}
		}
		data->spr = data->spr->next;
	}
	data->spr = head;
}